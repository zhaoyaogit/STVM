#include    "tvm.h"
#include    "tmain.h"

#define    TBL_USER_INFO            20

typedef struct  __TBL_USER_INFO
{
   long    acct_id;
   char    user_no[21];
   char    user_type[2];
   char    user_nm[81];
   char    user_addr[161];
   char    user_phone[31];
}dbUser;

long    lGroupUserInfo()
{
    size_t  i, lRow = 0;
    dbUser  stUser, *pstUser = NULL;
    SATvm   *pstSavm = (SATvm *)pGetSATvm();
 
    /* 初始化TBL_USER_INFO表，每张表都需要初始化一次, 对于表重建后，需要重新初始化一次。*/          
    if(RC_SUCC != lInitSATvm(pstSavm, TBL_USER_INFO))
    {
        fprintf(stderr, "init failed, err:(%d)(%s)\n", pstSavm->m_lErrno, sGetTError(pstSavm->m_lErrno));
        return RC_FAIL;
    }
 
    conditinit(pstSavm, stUser, TBL_USER_INFO);                // 绑定变量
    stringset(pstSavm, stUser, user_type, "1");                // 查询条件赋值
 
    decorate(pstSavm, dbUser, user_nm, GROUP_BY | ORDER_ASC);
    decorate(pstSavm, dbUser, user_phone, GROUP_BY | ORDER_DESC);
    if(RC_SUCC != lGroup(pstSavm, &lRow, (void **)&pstUser))
    {
        fprintf(stderr, "Group error: (%d) (%s)\n", pstSavm->m_lErrno, sGetTError(pstSavm->m_lErrno));
        return RC_FAIL;
    }

    for(i = 0; i < lRow; i ++)
        fprintf(stdout, "user_nm:%s, user_phone:%s\n", pstUser[i].user_nm, pstUser[i].user_phone);

    TFree(pstUser);

    return RC_SUCC;
}

int   main(int argc, char *argv[])
{
    if(RC_SUCC != lGroupUserInfo())
        return RC_FAIL;

    return RC_SUCC;
}


