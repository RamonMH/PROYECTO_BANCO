#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <time.h>

gotoxy(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

struct nodo
{
    char fname[20], sname[20], ftipocu[20], fnaci[20], cuent[10];
    float money;
    nodo *ant, *sig;
}*p=NULL, *f, *aux;

using namespace std;

char nomaux[20], ctaux[10], conc[50], con;
float retirar, dep;
int opc, ref;

void portada();
void marco();
void clientes();

void agregarArchivo(char path []) //LISTA
{
	system("cls");
    FILE *archivo;
    char n[20], ap[20],tipo_cu[20], fNac[10], cuen[10];
    int cta;
    float s;
    
	cout<<"\t\t  ||||************************** BVBA *************************||||"<<endl<<endl<<endl;   	  
	
    archivo = fopen(path, "a"); 
    if(archivo != NULL)
    {
    	cta=5000+rand()%(10001);
        cout<<"\t\t\t\t  INGRESE NOMBRE: ";
        cin>>n;
        cout<<endl<<endl;
        cout<<"\t\t\t\t  INGRESE APELLIDO: ";
        cin>>ap;
        cout<<endl<<endl;
        cout<<"\t\t\t\t  FECHA DE NACIMIENTO: ";
        cin>>fNac;
        cout<<endl<<endl;
        cout<<"\t\t\t\t  TIPO DE CUENTA DESEADA: ";
        cin>>tipo_cu;
        cout<<endl<<endl;
		if(strcmp(tipo_cu,"Debito")==0 || strcmp(tipo_cu,"DEBITO")==0 || strcmp(tipo_cu,"debito")==0)
		{
			cout<<"\t\t\t\t  DEPOSITO POR APERTURA: ";
        	cin>>s;	
        	cout<<endl<<endl;
		}
		else if(strcmp(tipo_cu,"Credito")==0 || strcmp(tipo_cu,"CREDITO")==0 || strcmp(tipo_cu,"credito")==0)
		{
			cout<<"\t\t\t\t  LINEA DE CREDITO AUTORIZADA: ";
        	cin>>s;	
        	cout<<endl<<endl;
		}
		
		cout<<"CLIENTE DADO DE ALTA EXITOSAMENTE"<<endl<<endl;
        fprintf(archivo, "\n%d\t%s\t%s\t%s\t%s\t%f" ,cta, n, ap, fNac, tipo_cu, s);
        system("pause");
        
        fclose(archivo);
    }
    else
        cout<<"ARCHIVO NO ENCONTRADO\n";
}

void eliminar(char path[], char pa[]) //LISTA
{
	FILE *archivo, *temp;
	
	char cta[20], nombre[20], buscar[20], apellido[20],fecN[20], tcta[20];
    float cal,saldo, ns;
    int aux=0;
    
    temp = fopen(pa, "w");
    archivo = fopen(path, "r+"); 
    
    system("cls");
    system("mode con: cols=100 lines=30");
    
	cout<<"\t\t  ||||************************** BVBA *************************||||"<<endl<<endl<<endl;   	  
    
    if(archivo != NULL)
    {
        cout<<"\t\t\t\t  NUMERO DE CUENTA A ELIMINAR: ";
        cin>>buscar;
        cout<<endl<<endl;
        
        while (!feof(archivo))
        {     
			fscanf(archivo, "%s\t%s\t%s\t%s\t%s\t%f",cta, nombre, apellido, fecN, tcta, &saldo);
			
            if (strcmp(cta, buscar) == 0)
            {
                cout<<"\t\t\t\t  <--------------INFO CUENTA------------->"<<endl<<endl;
                cout<<"\t\t\t\t  CUENTA ---------------->"<<cta<<endl<<endl;
                cout<<"\t\t\t\t  NOMBRE ---------------->"<<nombre<<endl<<endl;
                cout<<"\t\t\t\t  APELLIDO -------------->"<<apellido<<endl<<endl;
                cout<<"\t\t\t\t  FECHA DE NACIMIENTO --->"<<fecN<<endl<<endl;
                cout<<"\t\t\t\t  TIPO DE CUENTA -------->"<<tcta<<endl<<endl;
                cout<<"\t\t\t\t  SALDO ----------------->"<<saldo<<endl<<endl;
                cout<<"\t\t\t\t  PRESIONA S PARA CONFIRMAR...";
                cin>>con;
                
				if(con=='s'||con=='S')
                {
                	cout<<"\t\t\t\t  CLIENTE ELIMINADO EXITOSAMENTE..."<<endl;;
                	system("pause");
				}
				else
				{
					fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%f",cta, nombre, apellido, fecN, tcta, saldo);	
					cout<<"\t\t\t\t  TRANSACCION CANCELADA"<<endl;
					system("pause");
				}
					
            }
            else
            {
            	fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%f",cta, nombre, apellido, fecN, tcta, saldo);	
			}
        }
        
        fclose(archivo);	
        fclose(temp);
        
        remove("prueba.txt");
        rename("tmp.txt", "prueba.txt");
    }
    else
        printf("Archivo NO encontrado\n");
}

void leerArchivo(char path[]) //LISTA
{
	system("cls");
	system("mode con: cols=130 lines=30");
    FILE *archivo;
    
    char nombre[20], apellido[20],tipo_cuenta[20], cuenta[10], fecN[10];
    float saldo;
    
	cout<<"||||**************************************************** BVBA ***************************************************||||"<<endl<<endl<<endl;   	  
	
    archivo = fopen(path, "r");  
    if(archivo != NULL)
    {
    	cout<<"CUENTA\t\tNOMBRE\t\tAPELLIDO\t\tFECHA DE NACIMIENTO\t\tTIPO DE CUENTA     SALDO"<<endl<<endl;
        while(!feof(archivo))
        {
            fscanf(archivo, "%s\t%s\t%s\t%s\t%s\t%f",cuenta, nombre, apellido, fecN, tipo_cuenta, &saldo);
            cout<<cuenta<<"\t\t"<<nombre<<"\t\t"<<apellido<<"\t\t\t"<<fecN<<"\t\t\t"<<tipo_cuenta<<"\t\t        "<<saldo<<"\n";
            if(p==NULL)
            {
                p=new(nodo);
                strcpy(p->cuent,cuenta);
                strcpy(p->fname,nombre);
                strcpy(p->sname,apellido);
          		strcpy(p->fnaci,fecN);
                strcpy(p->ftipocu,tipo_cuenta);
                p->money=saldo;

                p->sig=NULL;
                p->ant=NULL;
                f=p;
            }
            else
            {
                aux=new(nodo);
                strcpy(aux->cuent,cuenta);
                strcpy(aux->fname,nombre);
                strcpy(aux->sname,apellido);
          		strcpy(aux->fnaci,fecN);
                strcpy(aux->ftipocu,tipo_cuenta);
                aux->money=saldo;
                f->sig=aux;
                aux->ant=f;
                aux->sig=NULL;
                f=aux;
            }
        }
        fclose(archivo);
    }
    else
        cout<<"ARCHIVO NO ENCONTRADO\n";
        system("pause");
}

void imprimirListaID() //LISTA
{
	system("cls");
	system("mode con: cols=130 lines=30");

	cout<<"||||**************************************************** BVBA ***************************************************||||"<<endl<<endl<<endl;   	  
    nodo *ini;
    ini = p;

    cout<<"CUENTA\t\tNOMBRE\t\tAPELLIDO\t\tFECHA DE NACIMIENTO\t\tTIPO DE CUENTA     SALDO"<<endl<<endl;
    
	while(ini != NULL)
    {
        cout<<ini->cuent<<"\t\t"<<ini->fname<<"\t\t"<<ini->sname<<"\t\t\t"<<ini->fnaci<<"\t\t\t"<<ini->ftipocu<<"\t\t        "<<ini->money<<"\n";
        ini = ini->sig;
    }
    system("pause");
}

void imprimirListaDI() //LISTA
{
	system("cls");	
	system("mode con: cols=130  lines=30");
	cout<<"||||**************************************************** BVBA ***************************************************||||"<<endl<<endl<<endl;   	  
    nodo *ini;
    ini = f;
    cout<<"CUENTA\t\tNOMBRE\t\tAPELLIDO\t\tFECHA DE NACIMIENTO\t\tTIPO DE CUENTA     SALDO"<<endl<<endl;
    
    while(ini != NULL)
    {
        cout<<ini->cuent<<"\t\t"<<ini->fname<<"\t\t"<<ini->sname<<"\t\t\t"<<ini->fnaci<<"\t\t\t"<<ini->ftipocu<<"\t\t        "<<ini->money<<"\n";
        ini = ini->ant;
        //system("pause");
    }
    system("pause");
}

void buscar(char path[])  //LISTA
{
 	FILE *archivo;
    
	char cuenta[20], nomre[20], buscar[20], apellido[20],fecN[20],tipo_cuenta[20];
    float cal,saldo;
    int aux=0;
    
    archivo = fopen(path, "r+"); 
    
    system("cls");
	cout<<"\t\t  ||||************************** BVBA *************************||||"<<endl<<endl<<endl;   	  
    
    if(archivo != NULL)
    {
        cout<<"\t\t\t\t  INGRESA EL DATO DEL CLIENTE A BUSCAR: ";
        cin>>buscar;
        
        while (!feof(archivo))
        {
             
			fscanf(archivo, "%s\t%s\t%s\t%s\t%s\t%f",cuenta, nomre, apellido, fecN, tipo_cuenta, &saldo);
			
            if (strcmp(nomre, buscar ) == 0 || strcmp(apellido, buscar ) == 0 ||strcmp(cuenta, buscar ) == 0)
            {
                aux = 1;
                
				cout<<"\t\t\t\t  ***CLIENTE ENCONTRADO***"<<endl<<endl;
                
                cout<<"\t\t\t\t  <<-------DATOS DEL CLIENTE--------->>"<<endl<<endl;
                
                cout<<"\t\t\t\t  N.o CUENTA------------->"<<cuenta<<endl<<endl;
                cout<<"\t\t\t\t  NOMBRE DEL CLIENTE----->"<<nomre<<endl<<endl;
                cout<<"\t\t\t\t  APELLIDO CLIENTE------->"<<apellido<<endl<<endl;
                cout<<"\t\t\t\t  FECHA DE NACIMIENTO---->"<<fecN<<endl<<endl;
                cout<<"\t\t\t\t  TIPO DE CUENTA--------->"<<tipo_cuenta<<endl<<endl;
                cout<<"\t\t\t\t  SALDO ACTUAL----------->"<<saldo<<endl<<endl;
                
                system("pause");
            }
        }
        if (aux == 0)
        {
            printf("\t\t\t\t  CLIENTE INEXISTENTE\n");
        }
        fclose(archivo);
    }
    else
        printf("Archivo NO encontrado\n");
        
        system("pause");
}

void deposito(char path[], char pa[]) //LISTA
{
	FILE *archivo, *temp;
	
	char cta[20], nombre[20], buscar[20], apellido[20],fecN[20], tcta[20];
    float cal,saldo, ns;
    int aux=0;
    
    temp = fopen(pa, "w");
    archivo = fopen(path, "r+"); 
    
    system("cls");
    system("mode con: cols=100 lines=35");
    
	cout<<"\t\t  ||||************************** BVBA *************************||||"<<endl<<endl<<endl;   	  
    
    if(archivo != NULL)
    {
        cout<<"\t\t\t\t  NUMERO DE CUENTA A DEPOSITAR: ";
        cin>>buscar;
        cout<<endl<<endl;
        
        while (!feof(archivo))
        {     
			fscanf(archivo, "%s\t%s\t%s\t%s\t%s\t%f",cta, nombre, apellido, fecN, tcta, &saldo);
			
            if (strcmp(cta, buscar) == 0)
            {
                cout<<"\t\t\t\t  <--------------INFO CUENTA------------->"<<endl<<endl;
                cout<<"\t\t\t\t  CUENTA------------->"<<cta<<endl<<endl;
                cout<<"\t\t\t\t  NOMBRE DEL CLIENTE----->"<<nombre<<endl<<endl;
                strcpy(nomaux,nombre);
                strcpy(ctaux,cta);
                cout<<"\t\t\t\t  MONTO A DEPOSITAR: ";
                cin>>dep;
                ns=saldo+dep;
                cout<<endl<<endl;      
                cout<<"\t\t\t\t  REFERENCIA: ";
                cin>>ref;
        		cout<<endl<<endl;        
                cout<<"\t\t\t\t  CONCEPTO: ";
                cin>>conc;
                
                cout<<endl<<endl;
                cout<<"\t\t\t\t  <--------------VISTA PREVIA------------->"<<endl;
                cout<<"\t\t\t\t  CUENTA --------> "<<cta<<endl<<endl;
                cout<<"\t\t\t\t  BENEFICIARIO --> "<<nombre<<endl<<endl;
                cout<<"\t\t\t\t  REFERENCIA ----> "<<ref<<endl<<endl;
                cout<<"\t\t\t\t  CONCEPTO ------> "<<conc<<endl<<endl;
                cout<<"\t\t\t\t  MONTO ---------> $"<<dep<<endl<<endl;
                cout<<"\t\t\t\t  PRESIONA S PARA CONFIRMAR...";
                cin>>con;
				if(con=='s'||con=='S')
                {
                	cout<<"\t\t\t\t  TRANSACCION REALIZADA CON EXITO"<<endl;
                	fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%f" ,cta, nombre, apellido, fecN, tcta, ns);
                	system("pause");
				}
				else
				{
					fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%f",cta, nombre, apellido, fecN, tcta, saldo);	
					cout<<"\t\t\t\t  TRANSACCION CANCELADA"<<endl;
					system("pause");
				}
					
            }
            else
            {
            	fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%f",cta, nombre, apellido, fecN, tcta, saldo);	
			}
        }
        
        fclose(archivo);	
        fclose(temp);
        
        remove("prueba.txt");
        rename("tmp.txt", "prueba.txt");
    }
    else
        printf("Archivo NO encontrado\n");
}

void retiro(char path[],char pathh[])
{
	FILE *archivo, *temp;
    char cuenta[20], nombre[20], buscar[20], apellido[20],fecN[20],tipo_cuenta[20];
    float cal,saldo,retirar2;
    int aux=0;
    temp=fopen(pathh,"w");
    
    archivo = fopen(path, "r+"); 
    
    system("cls");
 	cout<<"\t\t  ||||************************** BVBA *************************||||"<<endl<<endl<<endl;   	  
 	
    if(archivo != NULL )
    {
        cout<<"\t\t\t\t  INGRESE SU NUMERO DE CUENTA: ";
        cin>>buscar;
        
    	cout<<endl<<endl;
	    while (!feof(archivo) )
        {
            fscanf(archivo, "%s\t%s\t%s\t%s\t%s\t%f",cuenta, nombre, apellido, fecN, tipo_cuenta, &saldo);
             
            if (strcmp(cuenta, buscar ) == 0)
            {
            	cout<<"\t\t\t\t  N.o CUENTA------------->"<<cuenta<<endl<<endl;
                cout<<"\t\t\t\t  NOMBRE DEL CLIENTE----->"<<nombre<<endl<<endl;
                strcpy(nomaux,nombre);
                strcpy(ctaux,cuenta);
	            cout<<"\t\t\t\t  INGRESE LA CANTIDAD A RETIRAR: ";
	            cin>>retirar;
               	cout<<endl<<endl;
                retirar2=saldo-retirar;
                cout<<"\t\t\t\t  TU NUEVO SALDO ES: $"<<retirar2<<endl;
				    
                fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%f",cuenta, nombre, apellido, fecN, tipo_cuenta, retirar2);                       
                system("pause");
            }
            
            else
            {
            	fprintf(temp, "\n%s\t%s\t%s\t%s\t%s\t%f",cuenta, nombre, apellido, fecN, tipo_cuenta, saldo);
			}     
     }
	fclose(archivo);
	fclose(temp);
	remove("prueba.txt");
	rename("tmp.txt", "prueba.txt");  
	}
    else
        printf("Archivo NO encontrado\n");
}

void consulta(char path[])  //LISTA
{
 	FILE *archivo;
    
	char cuenta[20], nombre[20], buscar[20], apellido[20],fecN[20],tipo_cuenta[20];
    float cal,saldo;
    int aux=0;
    
    archivo = fopen(path, "r+"); 
    
    system("cls");
 	cout<<"\t\t  ||||************************** BVBA *************************||||"<<endl<<endl<<endl;   	  
 	
    if(archivo != NULL)
    {
        cout<<"\t\t\t\t  INGRESA TU NUMERO DE CUENTA:  ";
        cin>>buscar;
        
        while (!feof(archivo))
        {
             
			fscanf(archivo, "%s\t%s\t%s\t%s\t%s\t%f",cuenta, nombre, apellido, fecN, tipo_cuenta, &saldo);
			
            if (strcmp(cuenta, buscar ) == 0)
            {
                cout<<"\t\t\t\t  <<-------DATOS DEL CLIENTE--------->>"<<endl<<endl;;
                
				cout<<"\t\t\t\t  N.o CUENTA -----------> "<<cuenta<<endl<<endl;
                cout<<"\t\t\t\t  NOMBRE DEL CLIENTE ---> "<<nombre<<endl<<endl;
                cout<<"\t\t\t\t  SALDO ACTUAL ---------> "<<saldo<<endl<<endl;
            }
        }
        fclose(archivo);
    }
        system("pause");
}

void ticketD(char ti[])
{
	int caja, trans;
	FILE *archivo;
			
	archivo=fopen(ti, "w");
	
	caja=1+rand()%(7);
	trans=1000000+rand()%(3000001);
	
	fprintf(archivo, "|||------------------------ BVBA ------------------------|||\n");
	fprintf(archivo, "||-----------------------------------------------------------||\n");
	fprintf(archivo, "||----------- SUCURSAL CULHUACAN -----------||\n");
	fprintf(archivo, "||  Caja No. %d    Transaccion No. %d       ||\n", caja, trans);
	fprintf(archivo, "||-----------------------------------------------------------||\n");
	fprintf(archivo, "|\t   BENEFICIARIO -> %s\t      |\n", nomaux);
	fprintf(archivo, "|\t   CUENTA -------> %s\t      |\n", ctaux);
	fprintf(archivo, "|\t   REFERENCIA ---> %d\t      |\n", ref);
	fprintf(archivo, "|\t   CONCEPTO -----> %s\t      |\n", conc);
	fprintf(archivo, "|\t   MONTO --------> $%.2f\t      |\n", dep);
	fprintf(archivo, "||-----------------------------------------------------------||\n");
	fprintf(archivo, "||-----------GRACIAS POR SU VISITA------------||\n");
	fclose(archivo);
}

void ticketR(char ti[])
{
	int caja, trans;
	FILE *archivo;
			
	archivo=fopen(ti, "w");
	
	caja=1+rand()%(7);
	trans=1000000+rand()%(3000001);
	
	fprintf(archivo, "|||------------------------ BVBA ------------------------|||\n");
	fprintf(archivo, "||-----------------------------------------------------------||\n");
	fprintf(archivo, "||----------- SUCURSAL CULHUACAN -----------||\n");
	fprintf(archivo, "||  Caja No. %d    Transaccion No. %d       ||\n", caja, trans);
	fprintf(archivo, "||-----------------------------------------------------------||\n");
	fprintf(archivo, "|\t   \t      \t \t      |\n");
	fprintf(archivo, "|\t   CUENTA -------> %s\t      |\n", ctaux);
	fprintf(archivo, "|\t   \t      \t \t      |\n");
	fprintf(archivo, "|\t   \t      \t \t      |\n");
	fprintf(archivo, "|\t   MONTO --------> $%.2f\t      |\n", retirar);
	fprintf(archivo, "||-----------------------------------------------------------||\n");
	fprintf(archivo, "||-----------GRACIAS POR SU VISITA------------||\n");
	fclose(archivo);
}

int main()
{
    int opc, op;
    
	portada();

	system("color 1F");
	setlocale(LC_ALL, "");
    
    srand(time(NULL));
    while (1)
    {
    	system("mode con: cols=100 lines=20");
    	system("cls");
    	cout<<"\t\t  ||||********************BIENVENIDO A BVBA********************||||"<<endl;
    	cout<<"\t\t  ||********************** MENU PRINCIPAL ***********************||"<<endl<<endl<<endl;
        cout<<"\t\t\t\t  Ingresa una opcion"<<endl<<endl<<endl;
        cout<<"\t\t\t\t  PASAR CON UN EJECUTIVO ------- (1)"<<endl<<endl;
        cout<<"\t\t\t\t  PASAR A PRACTICAJAS ---------- (2)"<<endl<<endl;
        cout<<"\t\t\t\t  INFORMES ADICIONAL ----------- (3)"<<endl<<endl;
        cout<<"\t\t\t\t  SALIR ------------------------ (4)"<<endl;
        cout<<"\t\t\t\t  ";
        cin>>opc;	
        switch (opc)
        {
            case 1:
            	system("cls");
            	system("mode con: cols=100 lines=30");
            	cout<<"\t\t  ||||********************BIENVENIDO A BVBA********************||||"<<endl;
            	cout<<"\t\t  ||*********************** MENU EJECUTIVO **********************||"<<endl<<endl;
            	cout<<"\t\t\t\t  Ingresa una opcion"<<endl<<endl<<endl;
				cout<<"\t\t\t\t  APERTURA DE CUENTA -------------- (1)"<<endl<<endl;
				cout<<"\t\t\t\t  VER CUENTAHABIENTES ------------- (2)"<<endl<<endl;
				cout<<"\t\t\t\t  BUSCAR CUENTAHABIENTE ----------- (3)"<<endl<<endl;
				cout<<"\t\t\t\t  IMPRIMIR LISTA DE DI ------------ (4)"<<endl<<endl;
        		cout<<"\t\t\t\t  IMPRIMIR LISTA DE ID ------------ (5)"<<endl<<endl;
        		cout<<"\t\t\t\t  ELIMINAR CUENTA CUENTAHABIENTE -- (6)"<<endl<<endl;
				cout<<"\t\t\t\t  REGRESAR AL MENU PRINCIPAL ------ (7)"<<endl;
				cout<<"\t\t\t\t  ";
				cin>>op;
				
				switch(op)
				{
					case 1: agregarArchivo("prueba.txt"); break;
					case 2: leerArchivo("prueba.txt"); break;
					case 3: buscar("prueba.txt"); break;
					case 4: imprimirListaDI(); break;
		    		case 5: imprimirListaID(); break;   
		    		case 6: eliminar("prueba.txt", "tmp.txt");  break;
				}
            break;
            
            case 2:
            	system("cls");   
            	cout<<"\t\t  ||||********************BIENVENIDO A BVBA********************||||"<<endl;
            	cout<<"\t\t  ||*********************** PRACTICAJA BVBA *********************||"<<endl<<endl;
            	cout<<"\t\t\t\t  Ingresa una opcion"<<endl<<endl<<endl;
            	cout<<"\t\t\t\t  DEPOSITO A CUENTA ---------- (1)"<<endl<<endl;
            	cout<<"\t\t\t\t  RETIRO EN EFECTIVO --------- (2)"<<endl<<endl;
				cout<<"\t\t\t\t  CONSULTAR SALDO ------------ (3)"<<endl<<endl;
				cout<<"\t\t\t\t  REGRESAR AL MENU PRINCIPAL - (4)"<<endl;
            	cout<<"\t\t\t\t  ";
            	cin>>op;
            	
            	switch(op)
            	{
            		case 1: 
						deposito("prueba.txt", "tmp.txt"); 
						ticketD("ticket.txt"); 
					break;
            		
					case 2: 
						retiro("prueba.txt", "tmp.txt"); 
						ticketR("ticket.txt");
					break;
					
					case 3:
						consulta("prueba.txt");
					break;
				}
            break;
            
            case 3: clientes (); break;
            
            case 4: exit(0); break;
        }
    }
}

void clientes()
{
	int opp;
	
	system("cls");
	
	cout<<"\t\t  ||||********************BIENVENIDO A BVBA********************||||"<<endl;
	cout<<"\t\t  ||*********************SERVICIO AL CLIENTE*********************||"<<endl<<endl;
	cout<<"\t\t\t\t  REQUISITOS APERTURA DE CUENTA ------ (1)"<<endl<<endl;
	cout<<"\t\t\t\t  REQUISITOS TARJETA DE CREDITO ------ (2)"<<endl<<endl;
	cout<<"\t\t\t\t  REQUISITOS TARJETA DE DEBITO ------- (3)"<<endl<<endl;
	cout<<"\t\t\t\t  QUEJAS Y RECLAMOS A SERVICIOS--------(4)"<<endl;        	
	cout<<"\t\t\t\t  ";
	cin>>opp;
            	
	switch(opp)
	{
		case 1: 
			system("cls");
			system("mode con: cols=100 lines=30");
		   	cout<<"\t\t ||||************************** BVBA *************************||||"<<endl;   	  
		   	cout<<"\t\t |||*************** REQUESITOS APERTURA DE CUENTA *************|||"<<endl<<endl;   	  
	       	cout<<"\t\t Acudir a cualquier sucursal del Grupo Financiero BVBA Bancomer de\n"; 
			cout<<"\t\t tu preferencia, y llevar la siguiente documentación:\n";
			cout<<"\t\t 1.Edad Minima de 18 años \n";
			cout<<"\t\t 2.Acta de Nacimiento\n"; 
			cout<<"\t\t 3.Identificación oficial y comprobante de domicilio. \n";
	       	cout<<"\t\t 4.Contratación en sucursal.\n\n";      
	       	system("pause");
        break;
         
        case 2: 
        	system("cls");
        	system("mode con: cols=100 lines=30");
           	cout<<"\t\t ||||************************** BVBA *************************||||"<<endl;   	  
           	cout<<"\t\t |||************** REQUESITOS TARJETA DE CREDITO **************|||"<<endl<<endl;   	  
           	cout<<"\t\t 1.Residentes en la República Mexicana.\n";
			cout<<"\t\t 2.Edad mínima de 18 años.\n"; 
			cout<<"\t\t 3.Ingresos mínimos mensuales: $6,000.00.\n";
           	cout<<"\t\t 4.Identificación oficial vigente.\n ";
			cout<<"\t\t 5.Comprobante de domicilio.\n"; 
			cout<<"\t\t 6.Solicitud de tarjeta de crédito y consulta al buró de crédito\n\n";
           	system("pause");
	    break;
        
		case 3:
			system("cls");
			system("mode con: cols=100 lines=20");
		   	cout<<"\t\t ||||************************** BVBA *************************||||"<<endl;   	  
		   	cout<<"\t\t |||**************** REQUESITOS TARJETA DEBITO ****************|||"<<endl<<endl<<endl;   	  
		   	cout<<"\t\t 1.Una identificación con fotografía vigente.\n"; 
			cout<<"\t\t 2.Un comprobante de domicilio con no más de 3 meses de antigüedad.\n";
		   	cout<<"\t\t 3.Ser mayor de 18 años\n\n";
		   	system("pause");
		break;
			   
		case 4:
			system("cls");
			system("mode con: cols=100 lines=30");
			cout<<"\t\t ||||************************** BVBA *************************||||"<<endl;   	  
			cout<<"\t\t ||********************** QUEJAS Y RECLAMOS ********************||"<<endl<<endl;   	  
	      	cout<<"\t\t En el caso de que la respuesta de las aclaraciones o reclamaciones\n"; 
			cout<<"\t\t que presentas ante nuestra Institución no cubre sus expectativas,\n";
		  	cout<<"\t\t con gusto te atenderemos al teléfono 55 1998 8039 y del interior al\n";
			cout<<"\t\t 800 112 2610.\n\n"; 
		  	cout<<"\t\t También puedes enviar un correo electrónico a une.mx@bvba.com o\n"; 
			cout<<"\t\t ponerte en contacto con nosotros en Lago Alberto 320 (entrada por\n"; 
			cout<<"\t\t Mariano Escobedo 303), colonia Anáhuac, código postal 11320, alcaldía\n";
			cout<<"\t\t Miguel Hidalgo, Ciudad de México, Business Center Planta Baja,\n"; 
			cout<<"\t\t entre Laguna de Mayrán y Lago Alberto\n\n";
			system("pause");
		break;			  	   		  
	}	
}

void portada()
{
	system("color 74");
	int cont, i,x, y;
	gotoxy(0,0);
	for(i=0;i!=120;i++)
	{
		cout<<"-";
	}
	
	for(cont= 1,x=30,y=1,i=0;cont<=16;cont++,x--,y++)
	{
		gotoxy(x,y);
		for(i=0;i!=10;i++)
		{
			cout<<"I";
		}
		cout<<"\n";
	}
		for(cont= 1,x=45,y=1,i=0;cont<=16;cont++,x--,y++)
	{
		gotoxy(x,y);
		for(i=0;i!=10;i++)
		{
			cout<<"P";
		}
		cout<<"\n";
	}
	for(cont = 1,x=55,y=1;cont<=4;cont++,x++,y++)
	{
	    gotoxy(x,y);
        for(i=0;i!=10;i++)
        {
	    cout<<"P";
        }
        cout<<"\n";
    }
    	for(cont = 1,x=58,y=4;cont<=3;cont++,x--,y++)
	{
	    gotoxy(x,y);
        for(i=0;i!=10;i++)
        {
	    cout<<"P";
        }
        cout<<"\n";
    }
        gotoxy(49,6);
    cout<<"      PPPPPPPPPPP";
    gotoxy(48,7);
    cout<<"     PPPPPPPPPPP";
    gotoxy(47,8);
    cout<<"    PPPPPPPPPP";
    gotoxy(46,9);
    cout<<"PPPPPPPPPPPP";
    gotoxy(38,10);
    cout<<"PPPPPPPPPPPPPPPP";
    
	for(cont= 1,x=75,y=1,i=0;cont<=16;cont++,x--,y++)
	{
		gotoxy(x,y);
		for(i=0;i!=10;i++)
		{
			cout<<"N";
		}
		cout<<"\n";
	}
		for(cont= 1,x=80,y=1,i=0;cont<=16;cont++,y++)
	{
		gotoxy(x,y);
		for(i=0;i!=10;i++)
		{
			cout<<"N";
		}
		cout<<"\n";
	}
		for(cont= 1,x=100,y=1,i=0;cont<=16;cont++,x--,y++)
	{
		gotoxy(x,y);
		for(i=0;i!=10;i++)
		{
			cout<<"N";
		}
		cout<<"\n";
	}
	gotoxy(0,17);
	for(i=0;i!=200;i++)
	{
		cout<<"-";
	}
	cout<<"\n";
		gotoxy(0,18);
	for(i=0;i!=60;i++)
	{
		cout<<"<>";
	}
	gotoxy(0,19);
	for(i=0;i!=120;i++)
	{
		cout<<"-";
	}
	cout<<"\n";
	
	gotoxy(50,20);
	cout<<"ESIME CULHUACAN";
	gotoxy(20,22);
	cout<<"INGENIERIA EN COMPUTACION";
	gotoxy(20,24);
	cout<<"ESTRUCUTRA DE DATOS";
	gotoxy(70,22);
	cout<<" 3CM25";
	gotoxy(70,24);
	cout<<"MENDOZA HERNANDEZ RAMON";
	gotoxy(70,25);
	cout<<"HERNANDEZ ROJAS LUIS MARIO";
	gotoxy(20,26);
	cout<<"PROFA. AZUARA PEREZ LORENA";
	gotoxy(40,28);
	system("pause");
}

/*void marco()
{
	gotoxy(1,0);
		for(int i=0;i<118;i++)
		{
			cout<<"-";
		}
		for(int i=0,y=1;i<27;i++,y++)
		{
			gotoxy(1,y);
			cout<<"|";
		}
		gotoxy(1,10);
		for(int i=0;i<118;i++)
		{
			cout<<"-";
		}
		for(int i=0,y=1;i<27;i++,y++)
		{
			gotoxy(41,y);
			cout<<"|";
		}
}*/
