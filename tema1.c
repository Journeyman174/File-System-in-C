/* OLARU Gabriel-322CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 80

struct Dir;
struct File;

typedef struct Dir{
	char *name;
	struct Dir* parent;
	struct File* head_children_files;
	struct Dir* head_children_dirs;
	struct Dir* next;
} Dir, *TDir;

typedef struct File {
	char *name;
	struct Dir* parent;
	struct File* next;
} File, *TFile;


//Aloca si initializeaza celula in lista de directoare

TDir AlocDir(TDir parinte, char *nume)          /* adresa celulei create sau NULL */
{ 
char * nume_d = malloc(strlen(nume)+1);
if(!nume_d)
{
	free(nume_d);
	nume_d = NULL;
	free(nume);
	nume = NULL;
	return NULL;
}
TDir aux = (TDir)malloc(sizeof(Dir));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { 
	aux->name = nume_d;                   /* (2,3) completeaza noua celula */
	strcpy(aux->name, nume);                   /* (2,3) completeaza noua celula */
	aux->parent = parinte;
	aux->head_children_files = NULL;
	aux->head_children_dirs = NULL;
	aux->next = NULL;
  }
   else
  	{
  	free(nume);
  	free(nume_d);
  	free(aux->name);
 	free(aux->parent);
 	free(aux->head_children_dirs);
 	free(aux->head_children_files);
 	free(aux->next);
	free(aux);
  	aux = NULL;
  	}
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

//Cauta in directorul curent directorul si in subdir
//Pointer director - este
//NULL - nu este

TDir EsteDir(TDir parinte, char *nume) 
{
TDir L = NULL;
if(parinte->head_children_dirs == NULL)
	{
		L = parinte;
		for (; L != NULL; L = L->next) 
 			{

 				if (strcmp(nume, L->name) == 0) 
 					{

 						return L;
 					}
 			}
	}
else
	{
		L = parinte->head_children_dirs;

 		for (; L != NULL; L = L->next) 
 			{

 				if (strcmp(nume, L->name) == 0) 
 					{

 						return L;
 					}
 			}
 	}
  return NULL;
}

//Cauta in directorul curent directorul 
//Pointer director - este
//NULL - nu este

TDir EsteDirC(TDir parinte, char *nume) 
{
TDir L = NULL;
	{
		L = parinte;
		for (; L != NULL; L = L->next) 
 			{
 				if (strcmp(nume, L->name) == 0) 
 					{
 						return L;
 					}
 			}
	}
  return NULL;
}

//Aloca si initializeaza celula in lista de fisiere

TFile AlocFile(TDir parinte, char *nume)          /* adresa celulei create sau NULL */
{ 
char * nume_f = malloc(sizeof(char)*strlen(nume)+1);
if(!nume_f)
{
	free(nume_f);
	nume_f = NULL;
	free(nume);
	nume = NULL;
	return NULL;
}

TFile aux = (TFile)malloc(sizeof(File));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { 
  	aux->name = nume_f;                   /* (2,3) completeaza noua celula */
  	strcpy(aux->name, nume);                   /* (2,3) completeaza noua celula */
    	aux->parent = parinte;
    	aux->next = NULL;
  }
  else
  	{
  	free(nume_f);
  	nume_f = NULL;
  	free(nume);
  	nume = NULL;
  	free(aux->name);
  	free(aux->parent);
  	free(aux->next);
  	free(aux);
 	aux = NULL;
  	}
return aux;             /* rezultatul este adresa noii celule sau NULL */
}

//Cauta in directorul curent fisierul nou creat
//Pointer fisier - este
//NULL - nu este

TFile EsteFis(TDir parinte, char *nume) {
TFile L = parinte->head_children_files;
 for (; L != NULL; L = L->next) 
 	if(strcmp(nume, L->name) == 0) return L;
 
 return NULL;
}

void touch (Dir* parent, char* name) {
	TFile aux, L;
	if(parent->head_children_files == NULL)
	{		
		parent->head_children_files = AlocFile(parent,name);
	}
	else
	{		
		if(EsteFis(parent, name) != NULL)
			printf("File already exists\n");
		else
		{
			aux = AlocFile(parent, name);
			for (L = parent->head_children_files; L->next != NULL; L = L->next); 
			L->next = aux;
		}
	}	
}

void mkdir (Dir* parent, char* name) {
	TDir aux, L, p;
	if(parent->head_children_dirs == NULL)
		{
		parent->head_children_dirs = AlocDir(parent, name);
		if(!parent->head_children_dirs)
		{
			free(parent->head_children_dirs);
			parent->head_children_dirs = NULL;
			return ;
		}
		else
		return;
		}
	else
		p = parent->head_children_dirs;
	if (EsteDir(p, name) != NULL) 
		printf("Directory already exists\n");
	else
	{
		for (L = p; L->next != NULL; L = L->next); 
		aux=AlocDir(parent, name);
		if(!aux)
		{
		free(aux->name);
		free(aux);
		aux = NULL;
		return;
		}
		L->next = aux;
	}
}

void ls (Dir* parent) {
	TDir d, p;
	TFile f;
	if(parent->parent == NULL)
		{
		p = parent->head_children_dirs;
		for (d = p; d != NULL; d = d->next)
		{
			printf("%s\n",d->name);
		}
		for (f = parent->head_children_files; f != NULL; f = f->next)
			{
			printf("%s\n", f->name);
			}
		}
	else
		{
			p = parent;
			for (d = p->head_children_dirs; d != NULL; d = d->next)
			{
				printf("%s\n",d->name);
			}
			for (f = p->head_children_files; f != NULL; f = f->next)
			{
				printf("%s\n", f->name);
			}	
		} 	 
}


void rm (Dir* parent, char* name) {
	TFile aux, L, L_ant;
	if(parent->head_children_files == NULL)
	{		
		printf("Could not find the file\n");
	}
	else
	{
		aux = EsteFis(parent, name);		
		if( aux!= NULL)
		{
			if(parent->head_children_files == aux) 
				parent->head_children_files = aux->next;
		else
			{
			for (L = parent->head_children_files; L != NULL; L_ant = L, L = L->next) 
				if (strcmp(name, L->name) == 0) 
					L_ant->next = aux->next;
			}
			free(aux->name);
			free(aux);
			aux = NULL;
		}		
		else
			printf("Could not find the file\n");
	}	
}

void delete_dir(TDir dir)
{
TDir aux;
TFile faux;
	while(dir->head_children_files)
	{
		faux = dir->head_children_files;
		dir->head_children_files = dir->head_children_files->next;
		free(faux->name);
		faux->name = NULL;
		free(faux);
		faux = NULL;
	}
	while(dir->head_children_dirs)
	{
		if (!dir->head_children_dirs) return ;
		delete_dir(dir->head_children_dirs);
    		aux = dir->head_children_dirs;
    		dir->head_children_dirs = dir->head_children_dirs->next;
  		free(aux->name);
  		aux->name = NULL;
  		free(aux);
    		aux = NULL;
    	}	
}
void rmdir (Dir* parent, char* name) {
TDir aux, L, L_ant;
	if(parent->head_children_dirs == NULL)
		{
			printf("Could not find the dir\n");
			return;
		}
	else
	{
		aux = EsteDir(parent->head_children_dirs, name);
		if (aux == NULL) 
		{
			printf("Could not find the dir\n");
		}
		else
		{
			delete_dir(aux);
			if(parent->head_children_dirs == aux) 
				parent->head_children_dirs = aux->next;
			else
			{
				for (L = parent->head_children_dirs; L != NULL; L_ant = L, L = L->next) 
					if (strcmp(name, L->name) == 0) 
						L_ant->next = aux->next;
			}
			free(aux->name);
			free(aux);
			aux = NULL;
			if(parent->parent != NULL)
				parent->head_children_dirs = NULL;
		}
	} 
}

void cd(Dir** target, char *name) {
	TDir aux;
	TDir parinte = *target;
	if (parinte->parent == NULL)
		{
		if (strcmp(name,"..") == 0) return;
		aux = EsteDirC(parinte->head_children_dirs, name);
		if ( aux == NULL) 
			{
				printf("No directories found!\n");
			}
		else
			{
				*target = aux;
			}
		}
	
	else
	{
		if (strcmp(name,"..") == 0)
		{
			*target = parinte->parent;
		}
		else
		{
			aux = EsteDir(parinte, name);
			if ( aux == NULL) 
				{
				printf("No directories found!\n");
				}
			else
			{
				*target = aux;
			}
		}
	}	
}

char *pwd (Dir* target) {
	char *cale = malloc(80);
	char *c = malloc(80);
	char *c1 = malloc(80);
	strcpy(cale,"/");
	strcat(cale, target->name);
	TDir L = target->parent;
	if(L == NULL)
		{
			free(c);
			free(c1);
			return cale;
		}
		
	else
	{
	for( ;L->parent != NULL; L = L->parent)
	{
		strcpy(c,"/");
		strcat(c, L->name);
		strcpy(c1, c);
		strcat(c1, cale);
		strcpy(cale, c1);
	}
	strcpy(c,"/home");
	strcat(c, cale);
	strcpy(cale, c);
	free(c);
	free(c1);
	return cale;
	}
}
void stop (Dir* target) {
	delete_dir(target);
}

void tree (Dir* target, int level) {
	TDir d;
	TFile f;
	if(!target) return;
	d = target->head_children_dirs;
	for(;d != NULL; level--, d = d->next)
		{
			char * tab = malloc(80);
			strcpy(tab,"");
			for(int i = 0; i < level; i++)	
				strcat(tab,"    ");
			printf("%s%s\n", tab, d->name);
			level++;
			tree(d, level);
			for(f = d->head_children_files; f != NULL; f = f->next)
				{
				strcat(tab,"    ");
				printf("%s%s\n", tab, f->name);
				}
			free(tab);
		}
	
	if(target->parent == NULL)
		for(f = target->head_children_files; f != NULL; f = f->next)
			printf("%s\n", f->name);
}

void mv(Dir* parent, char *oldname, char *newname) {
	TDir od, nd, od_ant, p, L, L_ant, aux;
	TFile of, nf, of_ant, f, F, faux, F_ant;
	
	od = EsteDir(parent, oldname);
	nd = EsteDir(parent, newname);
	of = EsteFis(parent, oldname);
	nf = EsteFis(parent, newname);
	
	if((od == NULL) && (of == NULL))
		{
		printf("File/Director not found\n"); 
		return;
		}
	if((nd != NULL) || (nf != NULL))
		{
		printf("File/Director already exists\n"); 
		return;
		}
	if(od != NULL)	// pentru directoare
		{
			p = parent->head_children_dirs;
			for(L = p; L->next != NULL; L_ant = L , L = L->next)
				if(strcmp(oldname, L->name) == 0) 
					{
					od_ant = L_ant;
					break;
					}
			for(L = p; L->next != NULL; L = L->next); 
			aux = AlocDir(parent, newname);
			if(!aux)
			{
				free(aux->name);
				free(aux);
				aux = NULL;
				return;
			} 
			L->next = aux;
			L->next->head_children_files = od->head_children_files;
			L->next->head_children_dirs = od->head_children_dirs;
			if(p == od)
				parent->head_children_dirs = od->next;
			else 
				od_ant->next = od->next;
			free(od->name);
			od->name = NULL;
			free(od);
			od = NULL;
		}
	
	if(of != NULL)	// ptr fisiere
		{
			f = parent->head_children_files;
			for(F = f; F->next != NULL; F_ant = F ,F = F->next)
				if(strcmp(oldname, F->name) == 0)
				{
				of_ant = F_ant;
				 break;
				 }
			for(F = f; F->next != NULL; F = F->next); 
			faux=AlocFile(parent, newname);
			if(!faux)
			{
				free(faux->name);
				free(faux);
				faux = NULL;
				return;
			} 
			F->next = faux;
			if(f == of)
				parent->head_children_files = of->next;
			else 
				of_ant->next = of->next;
			free(of->name);
			of->name = NULL;
			free(of);	
			of = NULL;				
		}
}

int main () {
	size_t len = 0;
	int gata = 0;
	
	char *cmd1 = "touch";
	char *cmd2 = "mkdir";
	char *cmd3 = "ls";
	char *cmd4 = "rm";
	char *cmd5 = "rmdir";
	char *cmd6 = "cd";
	char *cmd7 = "pwd";
	char *cmd8 = "stop";
	char *cmd9 = "tree";
	char *cmd10 = "mv";

//Construiesc inceput lista home
TDir home = NULL;
char * nume_home = malloc(5);
if (!nume_home)
{
	free(nume_home);
	return -1;
}

//copiez string nume_home="home";
strcpy(nume_home,"home");
TDir parinte = NULL;
home = AlocDir(parinte, nume_home);
if(!home)
{
	free(nume_home);
	nume_home = NULL;
	free(home->name);
	free(home);
	home = NULL;
	return -1;
}
TDir dir_curent = home; //directorul curent

char* line = NULL;
char* nume_dir = NULL;
char * nume_fis = NULL;

do
	{
		if (getline(&line,&len,stdin) == -1 || strlen(line) == 1)
			gata = 1;
		else
		{
		/*
		Summary:
			Reads from stdin a string and breaks it down into command and in
			case it needs into a name.
		*/
			if(line[strlen(line) - 1] == '\n')
   				line[strlen(line) - 1] = '\0' ; // se adauga \0 la sfarsit pentru parsare corecta
  			
  			char * cmd = strtok(line," ");

//procesare comenzi din stdin

//comanda touch

 			if (strcmp(cmd, cmd1) == 0){
 				char * nume_fis = strtok(NULL, "");
 				touch(dir_curent, nume_fis);
 			
 			}

//comanda mkdir

 			if (strcmp(cmd, cmd2) == 0){
	 			char * nume_dir = strtok(NULL, "");
 				mkdir(dir_curent, nume_dir);

 			}

//comanda ls

 			if (strcmp(cmd, cmd3) == 0){
 				ls(dir_curent);
 			
 			}

//comanda rm

 			if (strcmp(cmd, cmd4) == 0){
				char * nume_fis = strtok(NULL, "");
 				rm(dir_curent, nume_fis);
 			
 			}

//comanda rmdir

 			if (strcmp(cmd, cmd5) == 0){
				char * nume_dir = strtok(NULL, "");
 				rmdir(dir_curent, nume_dir);
 			
 			}
//comanda cd

 			if (strcmp(cmd, cmd6) == 0){
 				char * nume_dir = strtok(NULL, "");
 				cd(&dir_curent, nume_dir);
 			}
//comanda pwd

 			if (strcmp(cmd, cmd7) == 0){
 				char * cale = pwd(dir_curent);
 				printf("%s\n", cale);
 				free(cale);
 			
 			}
//comanda stop

 			if (strcmp(cmd, cmd8) == 0){
 				stop(home);
 				free(home->name);
				free(nume_home);
				nume_home = NULL;
				free(nume_dir);
				free(nume_fis);
				free(home);
				free(line);
				home = NULL;
				return 0;
 			}

//comanda tree

 			if (strcmp(cmd, cmd9) == 0){
 				int level = 0;
 				tree(dir_curent, level);
 			}

//comanda mv

 			if (strcmp(cmd, cmd10) == 0){
 				char * old_fis = strtok(NULL," ");
 				char * new_fis = strtok(NULL, "");
 				mv(dir_curent, old_fis, new_fis);
 			}
		}
	} while (gata == 0);
	return 0;
}