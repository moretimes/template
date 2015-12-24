import smtplib  
from email.MIMEText import MIMEText
from email.Header import Header
mailto_list=["moretimes@126.com", "moretimes@126.com"]
mail_host="smtp.163.com"
mail_user="sysuacmm"
mail_pass="acmmcb"
mail_postfix="163.com"
  
def send_mail(to_list,sub,content):
    me="hello"+"<"+mail_user+"@"+mail_postfix+">"
    msg = MIMEText(content,_subtype='html',_charset='gb2312')
    msg['Subject'] = sub
    msg['From'] = me
    msg['To'] = ";".join(to_list)
    try:
        s = smtplib.SMTP()
        s.connect(mail_host)
        s.login(mail_user,mail_pass)
        s.sendmail(me, to_list, msg.as_string())
        s.close()
        return True
    except Exception, e:
        print str(e)
        return False
if __name__ == '__main__':
    if send_mail(mailto_list,"hello","Test Content"):
        print "Success"
    else:
        print "Fail"

