#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Derry");
MODULE_DESCRIPTION("hello kernel");
static int num=0;
// 接收参数num，模块加载时指定num=xxx，可以设置该值
module_param(num, int, S_IRUGO);
// 模块加载时调用
static int __init hello_init(void)
{
    printk("hello kernel\n");
    printk("num = %d\n", num);
    return 0;
}
// 模块卸载时调用
static void hello_exit(void)
{
    printk("module exit\n");
    return;
}
// 注册加载和卸载函数
module_init(hello_init);
module_exit(hello_exit);