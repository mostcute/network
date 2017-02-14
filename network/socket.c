#include <stdio.h>  
#include <winsock2.h>  
#pragma comment(lib,"ws2_32.lib")	//��ws2_32.lib�ӵ�Linkҳ�����ӿ�  
#define PORT 15001					//ͨ�ŵĶ˿ڣ�ָ�������ˣ�
#define ERROR 0  
#define BUFFER_SIZE 1024			//ע�⣺��Server�����ݽ��ջ����� >= Client�����ݷ��ͻ����� ��������ɻ��������
/*
	�����ԭ��
		1�����������̴����׽���
		2�������ص�ַ�󶨵����������׽����ϣ�����Ԫ��{<ͨ��Э��>,<IP��ַ>,<�˿ں�>}�������ϱ�ʶ���׽���
		3�����׽����������ģʽ����׼��������������
*/
int main()  
{  
	WSADATA WSAData;  
	if(WSAStartup(MAKEWORD(2,0),&WSAData)==SOCKET_ERROR)  //����winsock ��WSAStartup()������Winsock DLL���г�ʼ��
	{  
		printf("Socket initialize fail!\n");  
		exit(1);  
	}  
	SOCKET sock;										//������̴����׽��־�������ڼ�����
	if((sock=socket(AF_INET,SOCK_STREAM,0))==ERROR)		//����socket()��������һ�����׽��֣������������ַ���ͣ��׽������ͣ�����Э�飩
	{ 
		printf("Socket create!\n");  
		WSACleanup();  
		exit(1);  
	}  
	struct sockaddr_in ServerAddr;			//sockaddr_in�ṹ������ʶTCP/IPЭ���µĵ�ַ����ǿ��ת��Ϊsockaddr�ṹ
	ServerAddr.sin_family=AF_INET;			//sin_family�ֶα�����ΪAF_INET����ʾ��Socket����Internet��
	ServerAddr.sin_port=htons(PORT);		//sin_port�ֶ�����ָ������˿ڣ�ע������ͻ
	ServerAddr.sin_addr.s_addr=INADDR_ANY;  //sin_addr�ֶ����ڰ�һ��IP��ַ����Ϊһ��4�ֽڵ������޷��ų����ͣ����ݲ�ͬ�÷����ɱ�ʾ���ػ�Զ��IP��ַ
	if(bind(sock,(LPSOCKADDR)&ServerAddr,sizeof(ServerAddr))==SOCKET_ERROR)  //����bind()���������ص�ַ�󶨵����������׽����ϣ����������ϱ�ʶ���׽���
	{   
		printf("Bind fail!\n");  
		closesocket(sock);  
		WSACleanup();  
		exit(1);  
	}  
	printf("Server Socket Port:%d\n",ntohs(ServerAddr.sin_port));  
	if(listen(sock,10)==SOCKET_ERROR)		//����listen()�������׽����������ģʽ��׼�������������󣬲�����������δ���ӵ��׽��������֣����ڵȴ����ӵ������г��ȣ�
	{ 
		printf("Listen fail!\n");  
		closesocket(sock);  
		WSACleanup();  
		exit(1);  
	}  

	SOCKET msgsock;			//����һ���µ��׽��֣����ڽ���accept�����ķ���ֵ������ʾ�Ѿ����ܵ��Ǹ��ͻ��˵����ӣ���������Client���������ݣ�
	char buf[BUFFER_SIZE];  //���ݽ��ջ�����
	while(1)  
	{  
		if((msgsock=accept(sock,(LPSOCKADDR)0,(int *)0))==INVALID_SOCKET)  //�������״̬�󣬵���accept()�������տͻ��˵��������󣬲������Ӵ���msgsock�׽��֣�ԭsock�׽��ּ������������ͻ�����������
		{  
			printf("Accept fail!\n");  
			continue;  
		}  
		memset(buf,0,sizeof(buf));											//��ʼ�����ݽ��ջ�����
		recv(msgsock,buf,BUFFER_SIZE,0);									//���տͻ��˷��͹���������  
		if(buf[0]=='e' && buf[1]=='x' && buf[2]=='i' && buf[3]=='t')		//"exit"����˳�����
		{  
			printf("The End.\n");  
			break;  
		}
		printf("C:\\Socket\\Server>%s",buf);  
		closesocket(msgsock);  
	}  

	closesocket(sock); //�ر��׽���  
	WSACleanup();	   //��ֹ��Winsock DLL��ʹ�ã����ͷ���Դ
	return 0;
}   