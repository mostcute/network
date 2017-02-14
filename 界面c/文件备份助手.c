#pragma comment(linker,"/SUBSYSTEM:Windows  /ENTRY:mainCRTStartup")
#include <gtk/gtk.h> 
#include<io.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<direct.h>
#include <windows.h>
#include <locale.h>

wchar_t * ANSIToUnicode( const char* str );
char * UnicodeToANSI( const wchar_t* str );
wchar_t * UTF8ToUnicode( const char* str );
char * UnicodeToUTF8( const wchar_t* str );
char* w2m(const wchar_t* wcs);
wchar_t* m2w(const char* mbs);
char* ANSIToUTF8(const char* str);
char* UTF8ToANSI(const char* str);
void quxinghao(char name[200]);
char  filescan(char *fileload,char* saveload1);
char  huanxiegang(char name[400]); ////功能一 ：换斜杠 
char  quweibiao(char name[200])	;////////功能二 ：去尾标 
int  filescan1(char* fileload);
//static void saomiao();
char saveload[300] = {"D:/backup"};  //存放的目录
int num = 0;
static void print_hello(GtkWidget*widget, gpointer data) 
{ g_print("HelloWorld\n"); }

static gboolean on_delete_event(GtkWidget*widget, GdkEvent *event, gpointer data)
{

g_print("delete event occurred\n");
return TRUE;

}
GtkWidget *entry_from;
GtkWidget *entry_goto;
GtkWidget *label_tishi;
FILE *fp2;
static void ppt()//按键扫描函数
{    
       char filecount[200] = {0};
       char *name1 = gtk_entry_get_text(entry_from);
	   char *name = UTF8ToANSI(name1);
	   num = 0;
	if(_stricmp(name,""))
	{  fp2 = fopen("filelist.txt","wt");
	   huanxiegang(name);
       filescan1(name);  
	   fclose(fp2);
	   sprintf(filecount, ANSIToUTF8("扫描完成，共有 %d 个文件 \n详情请见filelist.txt"),num);
	}
	else
	{ 
	  fp2 = fopen("filelist.txt","wt");
	  filescan1("");
	  fclose(fp2);
	  sprintf(filecount, ANSIToUTF8("未输入扫描地址\n如果继续选择备份将复制本程序目录,当前目录下有%d个文件\n详情请见filelist.txt"),num);
	}
     gtk_label_set_text(label_tishi,filecount);
	 
}
static void ppt2()//按键复制函数
{
    char filecount[100] = {0};
    char *name1 = gtk_entry_get_text(entry_from);
	char *name22 = gtk_entry_get_text(entry_goto);  
	char *name = UTF8ToANSI(name1);  
	char *name2 = UTF8ToANSI(name22);
	if(_stricmp(name,""))
	{
	    huanxiegang(name);
	  if(_stricmp(name2,""))
	  { 
		huanxiegang(name2);
		
	    filescan(name,name2);  
	  }
	  else
	  { 
	    filescan(name,saveload);
	  }
       	  
	}
	else
	{
	  if(_stricmp(name2,""))
	  { 
		huanxiegang(name2);
	   filescan("",name2); 
	  }
	  else
	  { 
	    filescan("",saveload);
	  }
	 //filescan("",saveload);
	// sprintf(filecount,"未输入扫描地址\n如果继续选择复制将复制本程序目录,当前目录下有%d个文件",num);
	}
	 gtk_label_set_text(label_tishi, ANSIToUTF8("文件备份成功"));
}

int main( int argc, char *argv[])
{ 
	GtkWidget *window; 
	GtkWidget *Grid1;
	 
	GtkWidget *label_from;
	GtkWidget *label_goto;
	
	GtkWidget *button_scan;
	GtkWidget *button_copy;
	setlocale(LC_ALL,"chs");

  gtk_init(&argc, &argv); 
      
  //窗口 
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
  gtk_window_set_default_size(GTK_WINDOW(window), 450, 250);
  gtk_window_set_title(GTK_WINDOW(window), "FILE backup helper");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); 
  
 // button=gtk_button_new_with_label("HelloWorld");
 // button = gtk_button_new_with_mnemonic ("click&copy(_B)");
  //网格1
  Grid1 = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window),Grid1);
  gtk_widget_show(Grid1);

  //文件地址输入文本框
  entry_from = gtk_entry_new();
  gtk_grid_attach(Grid1,entry_from, 0,0,10,1);
  gtk_widget_show(entry_from);
  gtk_entry_set_placeholder_text(entry_from, ANSIToUTF8("请输入扫描地址"));
  //文件地址输出文本框
  entry_goto = gtk_entry_new();
  gtk_grid_attach(Grid1,entry_goto, 0,1,10,1);
  gtk_widget_show(entry_goto);
  gtk_entry_set_placeholder_text(entry_goto, ANSIToUTF8("请输入备份地址"));
  //标签提示
  label_from = gtk_label_new(ANSIToUTF8("文件目录"));
  gtk_grid_attach(Grid1,label_from, 10,0,1,1);
  gtk_widget_show(label_from);
  //标签提示
  label_goto = gtk_label_new(ANSIToUTF8("备份目录"));
  gtk_grid_attach(Grid1,label_goto, 10,1,1,1);
  gtk_widget_show(label_goto);
   //标签提示
  label_tishi = gtk_label_new(ANSIToUTF8("输入文件地址扫描或备份"));
  gtk_grid_attach(Grid1,label_tishi, 0,2,20,2);
  gtk_widget_show(label_tishi);
  //按钮
  button_scan = gtk_button_new_with_label(ANSIToUTF8("扫描"));
  gtk_grid_attach(Grid1,button_scan, 11,0,1,1);
  gtk_widget_show(button_scan);
  //按钮
  button_copy = gtk_button_new_with_label(ANSIToUTF8("备份"));
  gtk_grid_attach(Grid1,button_copy, 11,1,1,1);
  gtk_widget_show(button_copy);


  g_signal_connect(button_scan,"clicked",G_CALLBACK(ppt),NULL);
  g_signal_connect(button_copy,"clicked",G_CALLBACK(ppt2),NULL);
  
  
  /*事件监听*/
 // g_signal_connect(window,"destroy",gtk_main_quit,NULL);
    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   // g_signal_connect(button_copy,"clicked",G_CALLBACK(saomiao),NULL);
	//g_signal_connect(button,"enter-notify-event",G_CALLBACK(print_hello),NULL);
   // g_signal_connect(window,"delete-event",G_CALLBACK(on_delete_event),NULL);
  //saomiao();
 
 /*包含关系*/ 
 //gtk_container_add(GTK_CONTAINER(window),button); 
  
  
  /*显示*/
  gtk_widget_show(window);
 // gtk_widget_show(button);


  gtk_main(); 
  return 0;
 }


/*     pressed          按下按钮
       released          释放按钮
       clichéd           点击按钮，这是“按下”和“释放”操作的组合
       enter                     鼠标移动到按钮上
       leave              鼠标离开按钮
	   */



/*static void saomiao()
{   
    _mkdir(saveload);//存放目录
    
	filescan("");
}*/


char  filescan(char* fileload,char* saveload)
{   char newname[300] = {0};
    char copyname[500] = {0};
	char selectname[500] = {0};
     char temp[1500] = {0};
	long findHander;
	struct _finddata_t data;
    char a = 0;
	_mkdir(saveload);
    if(!_stricmp(fileload,""))
    sprintf(temp,"*.*");
    else
    sprintf(temp,"%s/*.*",fileload);
    
	findHander =_findfirst(temp ,&data);
	 
	while(!_findnext(findHander ,&data) )
	{
		if ((data.attrib&_A_SUBDIR)==_A_SUBDIR)
		{    if(a !=0)
			{
			 char ziload[200] = {0}; 
             sprintf(newname,"%s/%s",saveload,data.name);
             if(!_stricmp(fileload,""))
			 {
				 sprintf(ziload,"%s",data.name);
             }
  
             else
             {
				 sprintf(ziload,"%s/%s",fileload,data.name);
             }
            
			 filescan(ziload,newname);
			}
              a++;
               
		}
		else
		{
		   if(_stricmp(data.name,"文件备份助手.exe"))
			{FILE *fp1;
             FILE *fp3;
	if(data.size<1024*1024)
	{		
             int buffer[16];       //对于一些小文件的特殊处理，否则文件会被忽略
			if(!_stricmp(fileload,""))
            {
            fp1 = fopen(data.name,"rb");
            sprintf(copyname,"%s/%s",saveload,data.name);
            fp3 = fopen(copyname,"wb");
            while(fread(buffer,sizeof(buffer),1,fp1) == 1)
            {
		     fwrite(buffer,sizeof(buffer),1,fp3); 
            } 
            fclose(fp3);
            fclose(fp1);
            }
			else
            {
			sprintf(selectname,"%s/%s",fileload,data.name);
            fp1 = fopen(selectname,"rb");
            sprintf(copyname,"%s/%s",saveload,data.name);
            fp3 = fopen(copyname,"wb");
            while(fread(buffer,sizeof(buffer),1,fp1) == 1)
            {
		     fwrite(buffer,sizeof(buffer),1,fp3); 
            } 
            fclose(fp3);
            fclose(fp1);
            }
	}
	 else
    {		
             int buffer[1024];
			// else
		    // int buffer[1024];
			if(!_stricmp(fileload,""))
            {
            fp1 = fopen(data.name,"rb");
            sprintf(copyname,"%s/%s",saveload,data.name);
            fp3 = fopen(copyname,"wb");
            while(fread(buffer,sizeof(buffer),1,fp1) == 1)
            {
		     fwrite(buffer,sizeof(buffer),1,fp3); 
            } 
            fclose(fp3);
            fclose(fp1);
            }
			else
            {
			
			sprintf(selectname,"%s/%s",fileload,data.name);
            fp1 = fopen(selectname,"rb");
            sprintf(copyname,"%s/%s",saveload,data.name);
            fp3 = fopen(copyname,"wb");
            while(fread(buffer,sizeof(buffer),1,fp1) == 1)
            {
		     fwrite(buffer,sizeof(buffer),1,fp3); 
            } 

            fclose(fp3);
            fclose(fp1);
            }
	}

			}
			
		}
     }



	return 0;
}


char  huanxiegang(char name[400]) 		////////////////////////////////////功能一 ：换斜杠 
{
	int i;

	for(i=0;name[i]!='\0';i++)
	{

		if(name[i]=='\\')
		{
			name[i]='/';
		}
	}
	
}
char quweibiao(char name[200])	///////////////////////////////////功能二 ：去尾标 
{
	int i,flag=0;
	for(i=0;name[i]!='\0';i++)
	{
        if(flag==0)
        {
		if(name[i]=='*')
		{
			if(name[i+1]=='.')
			{
				if(name[i+2]=='*')
				{
					name[i]='\0';
                    name[i+1]='\0';
                    name[i+2]='\0';
					flag=1;
				}
			}	
		}
        }
		if(flag==1)
		{
			name[i+1]=0; 
		}
	}	
}

void quxinghao(char name[200])
{ 
      if(name[0] == '*')
          name[0] = '\0';

}


int  filescan1(char* fileload)
{   char newname[300] = {0};
    char copyname[500] = {0};
     char temp[200] = {0};
	long findHander;
	struct _finddata_t data;
    char a = 0;
    if(fileload == "")
    sprintf(temp,"*.*");
    else
    sprintf(temp,"%s/*.*",fileload);
    
	findHander =_findfirst(temp ,&data);
	 
	while(!_findnext(findHander ,&data) )
	{
		if ((data.attrib&_A_SUBDIR)==_A_SUBDIR)
		{   
             if(a !=0)
			{
			 char ziload[200] = {0}; 
             if(fileload == "")
			 {
				 sprintf(ziload,"%s",data.name);
             }
  
             else
             {
				 sprintf(ziload,"%s/%s",fileload,data.name);
             }
			 fprintf(fp2,"\nDocument Folder    %s\n\n",ziload);
            
			 filescan1(ziload);
			}
              a++;  
		}
		else
		{ sprintf(newname,"%s/%s",fileload,data.name);
		  fprintf(fp2,"%s\n",newname);
		  num++;			
		}
    }
	return 0;
}

wchar_t * ANSIToUnicode( const char* str )
{
     int textlen ;
     wchar_t * result;
     textlen = MultiByteToWideChar( CP_ACP, 0, str,-1, NULL,0 ); 
     result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
     memset(result,0,(textlen+1)*sizeof(wchar_t)); 
     MultiByteToWideChar(CP_ACP, 0,str,-1,(LPWSTR)result,textlen ); 
     return result; 
}

char * UnicodeToANSI( const wchar_t* str )
{
     char* result;
     int textlen;
     textlen = WideCharToMultiByte( CP_ACP, 0, str, -1, NULL, 0, NULL, NULL );
     result =(char *)malloc((textlen+1)*sizeof(char));
     memset( result, 0, sizeof(char) * ( textlen + 1 ) );
     WideCharToMultiByte( CP_ACP, 0, str, -1, result, textlen, NULL, NULL );
     return result;
}

wchar_t * UTF8ToUnicode( const char* str )
{
     int textlen ;
     wchar_t * result;
     textlen = MultiByteToWideChar( CP_UTF8, 0, str,-1, NULL,0 ); 
     result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
     memset(result,0,(textlen+1)*sizeof(wchar_t)); 
     MultiByteToWideChar(CP_UTF8, 0,str,-1,(LPWSTR)result,textlen ); 
     return result; 
}

char * UnicodeToUTF8( const wchar_t* str )
{
     char* result;
     int textlen;
     textlen = WideCharToMultiByte( CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL );
     result =(char *)malloc((textlen+1)*sizeof(char));
     memset(result, 0, sizeof(char) * ( textlen + 1 ) );
     WideCharToMultiByte( CP_UTF8, 0, str, -1, result, textlen, NULL, NULL );
     return result;
}
/*宽字符转换为多字符Unicode - ANSI*/
char* w2m(const wchar_t* wcs)
{
      int len;
      char* buf;
      len =wcstombs(NULL,wcs,0);
      if (len == 0)
          return NULL;
      buf = (char *)malloc(sizeof(char)*(len+1));
      memset(buf, 0, sizeof(char) *(len+1));
      len =wcstombs(buf,wcs,len+1);
      return buf;
}
/*多字符转换为宽字符ANSI - Unicode*/
wchar_t* m2w(const char* mbs)
{
      int len;
      wchar_t* buf;
      len =mbstowcs(NULL,mbs,0);
      if (len == 0)
          return NULL;
      buf = (wchar_t *)malloc(sizeof(wchar_t)*(len+1));
      memset(buf, 0, sizeof(wchar_t) *(len+1));
      len =mbstowcs(buf,mbs,len+1);
      return buf;
}

char* ANSIToUTF8(const char* str)
{
     return UnicodeToUTF8(ANSIToUnicode(str));
}

char* UTF8ToANSI(const char* str)
{
     return UnicodeToANSI(UTF8ToUnicode(str));
}

