#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "sched.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "kernel.h"
#include "hd.h"
#include "blk_drv.h"

PRIVATE void free_inode(struct m_inode *inode);

PUBLIC void copy_d2m_inode(struct m_inode *m,struct d_inode *d)
{
	if(!m || !d)
	{
		panic("copy inode error\n");
	}
	m->i_mode = d->i_mode;
	m->i_size = d->i_size;
	m->i_start_sect = d->i_start_sect;
	m->i_nr_sects = d->i_nr_sects;
}

PUBLIC void sync_dev(int dev)
{
}
PUBLIC void write_inode(struct m_inode *inode)
{
	if(!inode->i_dirt || !inode->i_dev)
		return;
	u16 dev = inode->i_dev;
	u16 num = inode->i_num;
	struct buffer_head *bh;
	struct super_block *sb = get_super_block(dev);
	int blk_nr = 1 + NR_SUPER_BLOCK_SECTS + sb->s_nimap_sects + sb->s_nzmap_sects + \
			(num -1)/(SECTOR_SIZE/INODE_SIZE);
	bh = getblk(dev,blk_nr);
	hd_rw(ROOT_DEV,blk_nr,1,ATA_READ,bh);
	*(struct d_inode *)(bh->b_data + ((num -1)%(SECTOR_SIZE/INODE_SIZE)) * INODE_SIZE) = *(struct d_inode *)inode;	
	hd_rw(ROOT_DEV,blk_nr,1,ATA_WRITE,bh);
	brelse(bh);
	inode->i_dirt = 0;
}
PUBLIC void read_inode(struct m_inode* inode)
{
	u16 dev = inode->i_dev;
	u16 num = inode->i_num;
//	struct d_inode *tmp;
	struct buffer_head *bh;
	struct super_block *sb = get_super_block(dev);
	int blk_nr = 1 + NR_SUPER_BLOCK_SECTS + sb->s_nimap_sects + sb->s_nzmap_sects + \
			(num -1)/(SECTOR_SIZE / INODE_SIZE);
	bh = getblk(dev,blk_nr);
	//将inode信息从磁盘读入到内存中
	hd_rw(ROOT_DEV,blk_nr,1,ATA_READ,bh);
	//gcc 3.4.3之后不支持左值强制类型转换
	*((struct d_inode *)inode) = *((struct d_inode *)(bh->b_data+ ((num -1)%(SECTOR_SIZE/INODE_SIZE)) * INODE_SIZE));
//	tmp  = ((struct d_inode *)(bh->b_data+ ((num -1)%(SECTOR_SIZE/INODE_SIZE)) * INODE_SIZE));
//	copy_d2m_inode(inode,tmp);
//	printk("read_inode %d\n",inode->i_size);	
	brelse(bh);
	
}
PUBLIC struct m_inode* get_empty_inode()
{
	struct m_inode *inode;
	static struct m_inode *p = inode_table;
	for(;p <= inode_table + NR_INODE;p++)
	{
//		printk("p->i_count = %d\tp->i_dirt = %d\t",p->i_count,p->i_dirt);
		if(p->i_count)
			continue;
		else
		{
			if(!p->i_dirt)
			{
				inode = p;
				break;
			}
		}
	}
	if(inode)
	{
		memset(inode,0,sizeof(struct m_inode));
		inode->i_count = 1;
	} 
	return inode;
}
PRIVATE int _bmap(struct m_inode *inode,int block,int flag)
{
	if(block < 0)
		panic("_bmap : block < 0");	
	return 0;	
}
PUBLIC int bmap(struct m_inode *inode,int block)
{
	return _bmap(inode,block,0);
}

PUBLIC int create_block(struct m_inode *inode,int block)
{
	return _bmap(inode,block,1);
}
//从设备dev上查找num号的inode
PUBLIC struct m_inode* iget(int dev,int num)
{
	struct m_inode *inode,*empty;
	if(!dev)
	{
		panic("iget with dev == 0\n");
	}
	//	empty = get_empty_inode();

	inode = inode_table;
	//在inode_table中寻找一个可用的inode
	while(inode < inode_table + NR_INODE)
	{
		if(inode->i_dev != dev || inode->i_num != num)
		{
			inode++;
			continue;
		}
		else
		{
			//			inode->i_count++;
			return inode;
		}
	}
	empty = get_empty_inode();
	if(empty == NULL)
	{
		return NULL;
	}
	inode = empty;
	inode->i_dev = dev;
	inode->i_num = num;
	read_inode(inode);
	inode->i_nr_sects = NR_DEFAULT_SECTS;
	return inode;
}

PUBLIC void iput(struct m_inode *inode)
{
	if(!inode)
		return;
	if(!inode->i_count)
	{
		//		panic("iput;trying to free free inode");
		return;
	}
	if(inode == root_inode)
	{
		return;
	}
	if(!inode->i_dev)
	{
		inode->i_count--;
		return;
	}
	if(S_ISBLK(inode->i_mode) || S_ISCHR(inode->i_mode))
	{
		sync_dev(inode->i_start_sect);
	}
	if(inode->i_count > 1)
	{
		inode->i_count--;
		return;
	}
	else
		free_inode(inode);	
	if(inode->i_dirt)
	{
		write_inode(inode);		
	}
	return;
}

PRIVATE void free_inode(struct m_inode *inode)
{
	struct super_block *sb;
	if(!inode)
		return;
	if(!inode->i_dev)
	{
		memset(inode,0,sizeof(struct m_inode));
		return;
	}
	if(inode->i_count > 1)
	{
		printk("trying to free inode with count = %d\n",inode->i_count);
		panic("free_inode");
	}
	if(!(sb = get_super_block(inode->i_dev)))
		panic("trying to free inode on nonexistent device");
	if(inode->i_num < 1 ||  inode->i_num > sb-> s_ninodes)
		panic("trying to free inode 0 or nonexistant inode");
	memset(inode,0,sizeof(struct m_inode));
}

PUBLIC int new_block(int dev)
{
	struct super_block *sb;
	int block_nr;
	if(!(sb = get_super_block(dev)))
		panic("triny to get new block from nonexistant device");
	block_nr = get_zmap_bit(dev);
	if(block_nr <= 0)
	{
			printk("there is no free block");
			return 0;
	}	
	else
		return block_nr;
	
}
