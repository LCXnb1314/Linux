#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#define argb8888_to_rgb565(color) ({ \
unsigned int temp = (color); \
((temp & 0xF80000UL) >> 8) | \
((temp & 0xFC00UL) >> 5) | \
((temp & 0xF8UL) >> 3); \
})

int width,height;
unsigned short * screen_base=NULL;

void lcd_draw_point(unsigned int x,unsigned int y,unsigned int color)
{
    unsigned short rgb565_color=argb8888_to_rgb565(color);

    if(x>=width) x=width-1;
    if(y>=height) y=height-1;
    screen_base[y*width+x]=rgb565_color;
}
int main(int argc,char *argv[])
{
    int fd;
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;
    unsigned int screen_size;
    unsigned int i;

    fd=open("/dev/fb0",O_RDWR);
    if(0>fd)
    {
        perror("open err");
        exit(-1);
    }
    if(ioctl(fd,FBIOGET_VSCREENINFO,&fb_var)!=0)
    {
        perror("ioctl 1 err");
        exit(-1);
    }
    if(ioctl(fd,FBIOGET_FSCREENINFO,&fb_fix)!=0)
    {
        perror("ioctl 2 err");
        exit(-1);
    }
    printf("屏幕分辨率是：%d*%d\n",fb_var.xres,fb_var.yres);
    printf("屏幕位深度是：%d\n",fb_var.bits_per_pixel);
    printf("一行的字节数：%d\n",fb_fix.line_length);
    width=fb_var.xres;
    height=fb_var.yres;
    screen_size=fb_fix.line_length*fb_var.yres;

    screen_base=mmap(NULL,screen_size,PROT_WRITE,MAP_SHARED,fd,0);
    if(MAP_FAILED==(void *)screen_base)
    {
        perror("mmap err");
        close(fd);
        exit(-1);
    }

    for(i=0;i<480;i++)
    {
        lcd_draw_point(i,52,0x345633);
        lcd_draw_point(i,53,0x345633);
        lcd_draw_point(i,54,0x345633);
        lcd_draw_point(i,55,0x345633);
        lcd_draw_point(i,56,0x345633);
        lcd_draw_point(i,57,0x345633);
    }
        

    munmap(screen_base,screen_size);
    close(fd);

    exit(1);
}