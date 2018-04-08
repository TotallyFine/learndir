# coding:utf-8
from __future__ import print_function
import MySQLdb

def _connect():
    """
    如何连接数据库
    """
    conn = MySQLdb.connect(host='127.0.0.1'
                           ,user='root'
                           ,passwd='mariadb123'
                           ,db='BookstoreDB')
    # 获得一个游标
    cur = conn.cursor()
    # 执行SQL语句 （返回值是查询表中的行数，影响的行数）
    reCount = cur.execute('select * from AuthorsTBL')
    # 获取返回的信息
    data = cur.fetchall()
    # 关闭数据库
    conn.close()

    print('The rows of this table is {}'.format(reCount))
    print(data)

if __name__ == '__main__':
    _connect()
