#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct user// 账号和密码
{
    char name[30];     // 用户名
    char password[30]; // 密码
    float money;       // 余额
    int vip;           // 会员状态
    struct user *next;
}user;

typedef struct things // 商品信息
{
    char name[40];    // 商品名称
    float price;      // 商品价格
    char birth[20];   // 生产日期
    char death[20];   // 过期日期
    char compony[40]; // 生产公司
    struct things *next;
}node;

node *init = NULL;
user *list = NULL;
int nodecount = 0;
void nodemake();       // 录入商品数据
void usermake();       // 录入用户数据
void freeall();        // 释放对应内存
void menu1();          // 主界面
void opt1();           // 主界面选项
void menu2();          // 账号界面
void opt2();           // 账号选项
void enter();          // 登录账号
void createuser();     // 创建账号
void save1();          // 保存用户信息
void changeps();       // 修改密码
void addm();           // 余额充值
void makevip();        // 升级会员
void menu3();          // 商品界面(老板)
void opt3(user *crt);  // 商品选项(老板)
void menu4();          // 商品界面(用户)
void opt4(user *crt);  // 商品选项(用户)
void buy(user *crt);   // 购买商品
node *add(node *init); // 添加商品
void changenode();     // 修改商品信息
void del();            // 删除商品
void find();           // 查询商品
void count();          // 统计商品
void sort();           // 排序商品
void save();           // 保存商品信息
void show(node *init); // 展示商品

int main()
{
    nodemake();
    usermake();
    menu1();
    opt1();
    freeall();
}
void menu1() // 主界面
{
    printf("******************************************************\n\n\n");
    printf("       欢迎来到aa大型超市网页系统     \n\n");
    printf("       1.进入系统                  \n\n");
    printf("       2.退出系统                  \n\n\n");
    putchar('\n');
    printf("       输入序号选择，回车确定        \n");
    printf("******************************************************\n\n\n");
}

void opt1() // 主界面选项
{
    int a;
    scanf("%d", &a);
    if (a == 1)
    {
        system("cls");
        printf("进入\n");
        menu2();
        opt2();
    }
    else if (a == 2)
    {
        system("cls");
        printf("退出成功\n");
        printf("欢迎下次光临\n");
        freeall();
        exit(0);
    }
    else
    {
        printf("请输入正确的序号\n");
        opt1();
    }
}

void menu2() // 账号界面
{
    printf("******************************************************\n\n\n");
    printf("    1.登录账号\n\n");
    printf("    2.创建账号\n\n");
    printf("    3.修改密码\n\n");
    printf("    4.余额充值\n\n");
    printf("    5.会员办理\n\n");
    printf("    6.返回主界面\n\n");
    putchar('\n');
    printf("       输入序号选择，回车确定        \n");
    printf("******************************************************\n\n\n");
}

void opt2() // 账号选项
{
    int a;
    scanf("%d", &a);
    if (a == 1)
    {
        system("cls");
        enter();
    }
    else if (a == 2)
    {
        system("cls");
        printf("开始创建\n");
        createuser();
        save1();
        system("cls");
        printf("创建成功");
        menu2();
        opt2();
    }
    else if (a == 3)
    {
        system("cls");
        printf("修改密码\n\n");
        changeps();
        menu2();
        opt2();
    }
    else if (a == 4)
    {
        system("cls");
        printf("开始充值\n");
        addm();
        save1();
        menu2();
        opt2();
    }
    else if (a == 5)
    {
        makevip();
        menu2();
        save1();
        opt2();
    }
    else if (a == 6)
    {
        system("cls");
        menu1();
        opt1();
    }
    else
    {
        system("cls");
        printf("请输入正确的序号\n");
        menu2();
        opt2();
    }
}

void menu3()
{
    printf("******************************************************\n\n\n");
    printf("    1.统计商品\n\n");
    printf("    2.添加商品\n\n");
    printf("    3.修改商品信息\n\n");
    printf("    4.删除商品\n\n");
    printf("    5.查找商品\n\n");
    printf("    6.排序商品\n\n");
    printf("    7.展示当前超市所有商品信息\n\n");
    printf("    8.保存本次操作\n\n");
    printf("    9.退出当前账号\n\n");
    putchar('\n');
    printf("       输入序号选择，回车确定        \n");
    printf("******************************************************\n\n\n");
}

void opt3(user *crt)
{
    int a;
    scanf("%d", &a);
    if (a == 7)
    {
        system("cls");
        printf("\n\n");
        show(init);
        menu3();
        opt3(crt);
    }
    else if (a == 3)
    {
        system("cls");
        changenode();
        system("cls");
        printf("修改完成，请继续\n");
        menu3();
        opt3(crt);
    }
    else if (a == 6)
    {
        system("cls");
        printf("******************************************************\n\n\n");
        printf("  请选择你要排序的方式:\n\n");
        printf("   1.价格排序\n");
        printf("   2.名称排序\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        printf("******************************************************\n\n\n");
        sort();
        system("cls");
        printf("排序完毕\n");
        menu3();
        opt3(crt);
    }
    else if (a == 2)
    {
        system("cls");
        init = add(init);
        system("cls");
        printf("\n添加成功\n");
        menu3();
        opt3(crt);
    }
    else if (a == 5)
    {
        int c;
        system("cls");
        printf("请选择你要查询的方式\n");
        printf("   1.名称查询\n");
        printf("   2.价格查询\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        printf("******************************************************\n\n\n");
        find();
        menu3();
        opt3(crt);
    }
    else if (a == 1)
    {
        int c;
        system("cls");
        printf("请选择你要统计的方式\n");
        printf("   1.按价格统计\n");
        printf("   2.按公司统计\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        printf("******************************************************\n\n\n");
        count();
        menu3();
        opt3(crt);
    }
    else if (a == 8)
    {
        system("cls");
        save();
        printf("保存成功，请继续操作\n");
        menu3();
        opt3(crt);
    }
    else if (a == 9)
    {
        system("cls");
        menu2();
        opt2();
    }
    else if (a == 4)
    {
        system("cls");
        del();
        menu3();
        opt3(crt);
    }
    else
    {
        system("cls");
        printf("请输入正确的序号\n");
        menu3();
        opt3(crt);
    }
}

node *add(node *init)
{
    node *t = (node *)malloc(sizeof(node));
    printf("请输入商品名称\n");
    scanf("%s", t->name);
    printf("请输入商品价格\n");
    scanf("%f", &t->price);
    printf("请输入商品生产日期\n");
    scanf("%s", t->birth);
    printf("请输入商品过期日期\n");
    scanf("%s", t->death);
    printf("请输入商品生产公司\n");
    scanf("%s", t->compony);
    if (init == NULL)
    {
        t->next = NULL;
        return t;
    }
    else
    {
        t->next = init;
        return t;
    }
}

void show(node *init)
{
    node *t = init;
    printf("商品名称\t\t价格\t\t    生产日期\t\t    保证日期\t\t    公司\n\n\n");
    while (t)
    {
        printf("%-24s", t->name);
        printf("%-20.2f", t->price);
        printf("%-24s", t->birth);
        printf("%-24s", t->death);
        printf("%s\n\n\n", t->compony);
        t = t->next;
    }
}

void createuser()
{
    user *t = (user *)malloc(sizeof(user));
    t->name[0] = '\0';
    t->password[0] = '\0';
    t->money = 0;
    t->vip = 0;
    char buf[40];
    printf("请输入用户名\n");
    scanf("%s", buf);
    user *p = list;
    while (p && strcmp(buf, p->name))
    {
        p = p->next;
    }
    if (p)
    {
        printf("你所创建的用户名已被其他用户使用，请重试\n");
        free(t);
        createuser();
    }
    else
    {
        strcpy(t->name, buf);
        printf("请输入密码\n");
        scanf("%s", buf);
        printf("重复输入一次密码\n");
        scanf("%s", t->password);
        if (!strcmp(buf, t->password))
        {
            printf("创建账号成功\n\n\n");
            if (!list)
            {
                t->next = NULL;
                list = t;
            }
            else
            {
                t->next = list;
                list = t;
            }
        }
        else
        {
            printf("两次输入密码不相同，请重试\n\n");
            free(t);
            createuser();
        }
    }
}
void changeps()
{
    char buf[40];
    char buf1[40];
    user *t = list;
    printf("请先输入你的用户名\n");
    scanf("%s", buf);
    while (t)
    {
        if (!strcmp(t->name, buf))
        {
            break;
        }
        t = t->next;
    }
    if (t)
    {
        printf("请输入你要修改的密码\n");
        scanf("%s", buf);
        printf("请重复输入一次密码\n");
        scanf("%s", buf1);
        if (strcmp(buf, buf1))
        {
            system("cls");
            printf("两次密码输入不相同，请重试\n");
            changeps();
        }
        else
        {
            system("cls");
            printf("修改成功，请您牢记您的密码\n");
            strcpy(t->password, buf);
            save1();
        }
    }
    else
    {
        system("cls");
        printf("该用户不存在,请重试\n\n");
    }
}

void save()
{
    FILE *fp;
    fp = fopen("/home/wlx/node.txt", "w");
    if (fp == NULL)
    {
        printf("打开文件失败\n");
        perror("fopen()");
        exit(1);
    }
    node *t = init;
    while (t)
    {
        fprintf(fp, "%s\n", t->name);
        fprintf(fp, "%.2f\n", t->price);
        fprintf(fp, "%s\n", t->birth);
        fprintf(fp, "%s\n", t->death);
        if (t->next)
            fprintf(fp, "%s\n", t->compony);
        else
            fprintf(fp, "%s", t->compony);
        t = t->next;
    }
    fclose(fp);
}

void save1()
{
    FILE *fp;
    fp = fopen("user.txt", "w");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    user *p = list;
    while (p)
    {
        fprintf(fp, "%s\n", p->name);
        fprintf(fp, "%s\n", p->password);
        fprintf(fp, "%.2f\n", p->money);
        if (p->next)
            fprintf(fp, "%d\n", p->vip);
        else
            fprintf(fp, "%d", p->vip);
        p = p->next;
    }
    fclose(fp);
}

void usermake()
{
    FILE *fp;
    char buf[40];
    fp = fopen("user.txt", "r");
    if (fp == NULL)
    {
        puts("文件打开失败\n");
        exit(1);
    }
    while (!feof(fp))
    {
        user *t = (user *)malloc(sizeof(user));
        fscanf(fp, "%s", buf);
        strcpy(t->name, buf);
        fscanf(fp, "%s", buf);
        strcpy(t->password, buf);
        fscanf(fp, "%f", &t->money);
        fscanf(fp, "%d", &t->vip);
        if (!list)
        {
            t->next = NULL;
            list = t;
        }
        else
        {
            t->next = list;
            list = t;
        }
    }
    fclose(fp);
}
void enter()
{
    char buf1[40];
    char buf2[40];
    printf("登录账号\n\n");
    printf("请输入你的账号\n\n");
    scanf("%s", buf1);
    printf("请输入你的密码\n\n");
    scanf("%s", buf2);
    user *t = list;
    while (t)
    {
        if (strcmp(t->name, buf1) == 0 && strcmp(t->password, buf2) == 0)
        {
            break;
        }
        t = t->next;
    }
    if (t)
    {
        system("cls");
        printf("登录成功，请您继续\n\n");
        if (!strcmp("laoban", t->name))
        {
            menu3();
            opt3(t);
        }
        else
        {
            menu4();
            opt4(t);
        }
    }
    else
    {
        system("cls");
        printf("密码输入错误或该用户不存在,请重试\n\n");
        menu2();
        opt2();
    }
}

void del()
{
    char buf[40];
    printf("请输入你要删除的的商品\n");
    scanf("%s", buf);
    node *t = init;
    node *p = NULL;
    while (t && strcmp(t->name, buf))
    {
        p = t;
        t = t->next;
    }
    if (t)
    {
        if (!p)
        {
            p = init;
            init = init->next;
            free(p);
        }
        else
        {
            p->next = t->next;
            free(t);
        }
        printf("删除成功，请继续\n\n");
        return;
    }
    else
    {
        printf("商品中没有此商品\n");
        return;
    }
}

void nodemake()
{
    FILE *fp;
    char buf[40];
    fp = fopen("node.txt", "r");
    if (fp == NULL)
    {
        puts("文件打开失败\n");
        exit(1);
    }
    while (!feof(fp))
    {
        node *t = (node *)malloc(sizeof(node));
        fscanf(fp, "%s", buf);
        strcpy(t->name, buf);
        fscanf(fp, "%f", &t->price);
        fscanf(fp, "%s", buf);
        strcpy(t->birth, buf);
        fscanf(fp, "%s", buf);
        strcpy(t->death, buf);
        fscanf(fp, "%s", buf);
        strcpy(t->compony, buf);
        if (!init)
        {
            t->next = NULL;
            init = t;
        }
        else
        {
            t->next = init->next;
            init->next = t;
        }
        nodecount++;
    }
    fclose(fp);
}

void freeall()
{
    user *t;
    node *p;
    while (init)
    {
        p = init;
        init = init->next;
        free(p);
    }
    while (list)
    {
        t = list;
        list = list->next;
        free(t);
    }
}

void buy(user *crt)
{
    char buf[40];
    float v;
    show(init);
    while (1)
    {
        printf("请选择你要购买的商品\n\n");
        scanf("%s", buf);
        node *t = init;
        while (t && strcmp(t->name, buf))
        {
            t = t->next;
        }
        if (t)
        {
            int a;
            if (crt->vip)
            {
                v = t->price * 0.8;
            }
            else
            {
                v = t->price;
            }
            if (crt->money - v < 0)
            {
                printf("你没有足够的钱买此商品\n");
                printf("输入1继续购买，输入2退出购买\n");
                scanf("%d", &a);
                if (a == 1)
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                printf("购买成功\n");
                crt->money -= v;
                printf("这是您购买后的余额:%.2f\n", crt->money);
                printf("输入1继续购买，输入2退出购买\n");
                scanf("%d", &a);
                if (a == 1)
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            printf("商品不存在,请重试\n");
        }
    }
}

void addm()
{
    char buf[40];
    system("cls");
    printf("请选择你要充值的用户名\n");
    scanf("%s", buf);
    user *t = list;
    while (t && strcmp(t->name, buf))
    {
        t = t->next;
    }
    if (t)
    {
        float v;
        printf("请输入你要充值的金额\n");
        scanf("%f", &v);
        t->money += v;
        system("cls");
        printf("充值成功\n");
        printf("这是该账户当前的余额:%.2f\n\n", t->money);
    }
    else
    {
        system("cls");
        printf("该用户不存在，请重试\n\n");
    }
}

void makevip()
{
    int a;
    system("cls");
    printf("这里是会员办理系统，您可以支付200元然后成为本超市的vip用户\n");
    printf("此后您在本店的购买的任何物品都可以享受八折优惠\n");
    printf("支付的200元将从您的余额中扣去，若余额不足请及时充值\n");
    printf("输入1进行办理，输入2返回上一级\n");
    scanf("%d", &a);
    if (a == 1)
    {
        char buf1[40];
        char buf2[40];
        system("cls");
        printf("请输入你的账号\n\n");
        scanf("%s", buf1);
        printf("请输入你的密码\n\n");
        scanf("%s", buf2);
        user *t = list;
        while (t)
        {
            if (strcmp(t->name, buf1) == 0 && strcmp(t->password, buf2) == 0)
            {
                break;
            }
            t = t->next;
        }
        if (t)
        {
            if (t->vip == 1)
            {
                system("cls");
                printf("您已是本店会员，无需办理\n\n");
                return;
            }
            system("cls");
            printf("办理成功\n\n");
            t->vip = 1;
            t->money -= 200;
        }
        else
        {
            system("cls");
            printf("密码输入错误或该用户不存在,请重试\n\n");
        }
    }
    else
    {
        system("cls");
        return;
    }
}

void menu4()
{
    printf("******************************************************\n\n\n");
    printf("    1.购买商品\n\n");
    printf("    2.查找商品\n\n");
    printf("    3.排序商品\n\n");
    printf("    4.统计商品\n\n");
    printf("    5.展示当前超市所有商品信息\n\n");
    printf("    6.退出当前账号\n\n");
    putchar('\n');
    printf("       输入序号选择，回车确定        \n");
    printf("******************************************************\n\n\n");
}

void opt4(user *crt)
{
    int a;
    scanf("%d", &a);
    if (a == 5)
    {
        system("cls");
        printf("\n\n");
        show(init);
        menu4();
        opt4(crt);
    }
    else if (a == 2)
    {
        int c;
        system("cls");
        printf("请选择你要查询的方式\n");
        printf("   1.名称查询\n");
        printf("   2.价格查询\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        printf("******************************************************\n\n\n");
        find();
        menu4();
        opt4(crt);
    }
    else if (a == 4)
    {
        int c;
        system("cls");
        printf("请选择你要统计的方式\n");
        printf("   1.按价格统计\n");
        printf("   2.按公司统计\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        printf("******************************************************\n\n\n");
        count();
        menu4();
        opt4(crt);
    }
    else if (a == 1)
    {
        system("cls");
        printf("开始购买\n");
        buy(crt);
        system("cls");
        printf("购买结束\n");
        save1();
        menu4();
        opt4(crt);
    }
    else if (a == 3)
    {
        system("cls");
        printf("******************************************************\n\n\n");
        printf("  请选择你要排序的方式:\n\n");
        printf("   1.价格排序\n");
        printf("   2.名称排序\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        printf("******************************************************\n\n\n");
        sort();
        system("cls");
        printf("排序完毕\n");
        menu4();
        opt4(crt);
    }
    else if (a == 6)
    {
        system("cls");
        menu2();
        opt2();
    }
    else
    {
        system("cls");
        printf("请输入正确的序号\n");
        menu4();
        opt4(crt);
    }
}

void sort()
{
    int a;
    int num, i;
    scanf("%d", &a);
    if (a == 1)
    {
        system("cls");
        printf("1.升序排序\n");
        printf("2.降序排序\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        node *t = (node *)malloc(sizeof(node));
        t->next = init;
        node *tail, *p, *q;
        scanf("%d", &a);
        if (a == 1)
        {
            for (i = 0; i < nodecount; i++)
            {
                p = t->next;
                q = p->next;
                tail = t;
                num = nodecount - i - 1;
                while (num--)
                {
                    if (p->price > q->price)
                    {
                        p->next = q->next;
                        q->next = p;
                        tail->next = q;
                    }
                    tail = tail->next;
                    p = tail->next;
                    q = p->next;
                }
            }
        }
        else
        {
            for (i = 0; i < nodecount; i++)
            {
                p = t->next;
                q = p->next;
                tail = t;
                num = nodecount - i - 1;
                while (num--)
                {
                    if (p->price < q->price)
                    {
                        p->next = q->next;
                        q->next = p;
                        tail->next = q;
                    }
                    tail = tail->next;
                    p = tail->next;
                    q = p->next;
                }
            }
        }
        init = t->next;
        free(t);
    }
    else
    {
        system("cls");
        printf("1.升序排序\n");
        printf("2.降序排序\n");
        putchar('\n');
        printf("       输入序号选择，回车确定        \n");
        node *t = (node *)malloc(sizeof(node));
        t->next = init;
        node *tail, *p, *q;
        scanf("%d", &a);
        if (a == 1)
        {
            for (i = 0; i < nodecount; i++)
            {
                p = t->next;
                q = p->next;
                tail = t;
                num = nodecount - i - 1;
                while (num--)
                {
                    if (strcmp(p->name, q->name) > 0)
                    {
                        p->next = q->next;
                        q->next = p;
                        tail->next = q;
                    }
                    tail = tail->next;
                    p = tail->next;
                    q = p->next;
                }
            }
        }
        else
        {
            for (i = 0; i < nodecount; i++)
            {
                p = t->next;
                q = p->next;
                tail = t;
                num = nodecount - i - 1;
                while (num--)
                {
                    if (strcmp(p->name, q->name) < 0)
                    {
                        p->next = q->next;
                        q->next = p;
                        tail->next = q;
                    }
                    tail = tail->next;
                    p = tail->next;
                    q = p->next;
                }
            }
        }
        init = t->next;
        free(t);
    }
}

void find()
{
    int a;
    printf("请选择你要查询的方式\n");
    scanf("%d", &a);
    system("cls");
    if (a == 1)
    {
        char buf[40];
        printf("请输入商品名称\n");
        scanf("%s", buf);
        node *t = init;
        while (t && strcmp(t->name, buf))
        {
            t = t->next;
        }
        system("cls");
        if (t)
        {
            printf("商品名称\t\t价格\t\t    生产日期\t\t    保证日期\t\t    公司\n\n\n");
            printf("%-24s", t->name);
            printf("%-20.2f", t->price);
            printf("%-24s", t->birth);
            printf("%-24s", t->death);
            printf("%s\n\n\n", t->compony);
        }
        else
        {
            printf("没有这样的商品\n");
        }
    }
    else
    {
        float c;
        printf("请输入商品价格\n");
        scanf("%f", &c);
        node *t = init;
        while (t && t->price != c)
        {
            t = t->next;
        }
        system("cls");
        if (t)
        {
            printf("商品名称\t\t价格\t\t    生产日期\t\t    保证日期\t\t    公司\n\n\n");
            printf("%-24s", t->name);
            printf("%-20.2f", t->price);
            printf("%-24s", t->birth);
            printf("%-24s", t->death);
            printf("%s\n\n\n", t->compony);
        }
        else
        {
            printf("没有这样的商品\n");
        }
    }
}

void count()
{
    int a;
    printf("请选择你要统计的方式\n");
    scanf("%d", &a);
    system("cls");
    if (a == 2)
    {
        int count = 0;
        char buf[40];
        printf("请输入公司名\n");
        scanf("%s", buf);
        node *t = init;
        system("cls");
        printf("商品名称\t\t价格\t\t    生产日期\t\t    保证日期\t\t    公司\n\n\n");
        while (t)
        {
            if (!strcmp(buf, t->compony))
            {

                printf("%-24s", t->name);
                printf("%-20.2f", t->price);
                printf("%-24s", t->birth);
                printf("%-24s", t->death);
                printf("%s\n\n\n", t->compony);
                count++;
            }
            t = t->next;
        }
        printf("这样的商品共有%d个\n", count);
    }
    else
    {
        int count = 0;
        float c;
        printf("请输入商品价格\n");
        scanf("%f", &c);
        node *t = init;
        system("cls");
        printf("商品名称\t\t价格\t\t    生产日期\t\t    保证日期\t\t    公司\n\n\n");
        while (t)
        {
            if (t->price == c)
            {

                printf("%-24s", t->name);
                printf("%-20.2f", t->price);
                printf("%-24s", t->birth);
                printf("%-24s", t->death);
                printf("%s\n\n\n", t->compony);
                count++;
            }
            t = t->next;
        }
        printf("这样的商品共有%d个\n", count);
    }
}
void changenode()
{
    char buf[40];
    printf("请输入你要修改的商品名称\n");
    scanf("%s", buf);
    node *t = init;
    while (t && strcmp(t->name, buf))
    {
        t = t->next;
    }
    if (t)
    {
        printf("请开始修改\n");
        printf("请输入商品名称\n");
        scanf("%s", t->name);
        printf("请输入商品价格\n");
        scanf("%f", &t->price);
        printf("请输入商品生产日期\n");
        scanf("%s", t->birth);
        printf("请输入商品过期日期\n");
        scanf("%s", t->death);
        printf("请输入商品生产公司\n");
        scanf("%s", t->compony);
    }
    else
    {
        printf("不存在这样的商品\n");
    }
}



