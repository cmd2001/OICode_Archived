@echo off
@color 2f
@echo        ��ӭʹ��һ��VPN������ɽ�ֹVPN����
@echo          �ٷ���վ��www.ymvpn.com
@echo               ��棺����168VPN������빺����ϵ���ߡ�
@echo                 QQ��1260016481 ���������������ȫ�����ߡ�
@echo #######################################################
@echo #######      ���潫Ҫ������ɽ�ֹVPN����        #######
@echo #######  ����������� ��������ֱ�ӹرմ���    #######
@echo #######          ������һ�㶼����               #######
@echo #######  ����������Ƶĸ����Ǿ�û�취�ˣ�ף���� #######
@echo #######################################################
pause
sc config Netman start= AUTO
sc start Netman
sc config rasman start= AUTO
sc start rasman
sc config tapisrv start= AUTO
sc start tapisrv
@echo           �����ֹ��� ��������˳�
@echo #######################################################
pause

exit