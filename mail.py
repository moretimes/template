# -*- coding: UTF-8 -*-
'''
发送txt文本邮件
小五义：http://www.cnblogs.com/xiaowuyi
'''
import smtplib
from email.mime.text import MIMEText
from time import sleep
mailto_list=[]
mail_host="smtp.126.com"  #设置服务器
mail_user="moretimes"    #用户名
mail_pass="wangtianyu&1995"   #口令
mail_postfix="126.com"  #发件箱的后缀

def send_mail(to_list,sub,content):
    me="SYSUACMM"+"<"+mail_user+"@"+mail_postfix+">"
    msg = MIMEText(content,_subtype='plain',_charset='utf-8')
    msg['Subject'] = sub
    msg['From'] = me
    msg['To'] = ";".join(to_list)
    try:
        server = smtplib.SMTP()
        server.connect(mail_host)
        server.login(mail_user,mail_pass)
        server.sendmail(me, to_list, msg.as_string())
        server.close()
        return True
    except Exception, e:
        print str(e)
        return False
if __name__ == '__main__':
    f = open('content', 'r')
    s = f.read();
    add = open('address', 'r')
    cnt = 500
    while True:
        cnt = cnt + 1
        term = add.readline()
        if not term:
            break
        print cnt
        if send_mail([term],"新手赛网络预选赛", s):
            print term + "发送成功"
        else:
            print term + "发送失败"
        sleep(5)

   # for a in mailto_list:
   #    print a
    #print mailto_list;

