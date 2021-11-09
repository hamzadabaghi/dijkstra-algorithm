#include<stdio.h>
#include<stdlib.h>
#define INFINITY 1000000

typedef struct Noeud {
	int info ;
	struct Noeud * suc ;
} noeud ;

typedef noeud *listeNoeuds ;

typedef struct ARC {
	noeud *s ;
	noeud *d ;
	int val ;
	struct ARC* suc ;
} arc;

typedef arc *listeArcs ;

typedef struct GRAPHE {
   listeNoeuds LN ;
   listeArcs LA;
}graphe ;

typedef struct STR_chemin 
{
 noeud *Dest ;
 noeud *Interm;
 int c;
 int etat ;
 struct STR_chemin *suc ;	
}cheminDijkstra;
typedef cheminDijkstra *listeDijkstra ;

//creation d'un noeud 
 noeud* creerNoeud (int v){
 	noeud *n;
	n= (noeud*) malloc(sizeof(noeud));
	if(n!=NULL) {
	n->info=v;
	n-> suc=NULL;

  }
  return n ;	
}
//creation d'un arc 
arc* creerArc(noeud* NS , noeud *ND , float v){
	arc *A ; 
	A=(arc*) malloc(sizeof(arc));
	if(A!=NULL){
	A->s=NS;
	A->d=ND;
	A->val=v;
	A->suc=NULL; 
      }
      return A ;	
}
//creation d'un graphe 
graphe creerGraphe(){
	graphe G ;
	G.LA=NULL;
	G.LN=NULL;
	return G ;
} 
//tester si le graphe est vide 
int grapheEstVide(graphe G){
	if(G.LN==NULL)
     {return 1;
		 }	
else	return 0;
}
//tester si le graphe ne contient aucun arc 
int aucunArc(graphe G){
	if(G.LA==NULL)
      return 1;   
	return 0;
}
//afficher les noeuds 
int afficherNoeudsGraphe(graphe G){
	
 noeud* n ;
    n=G.LN;
    if( grapheEstVide(G)==0){
	while(n!=NULL){
   	printf("%d ",n->info);
   	n=n->suc ;
   }
   return 1;}
   else
   return 0; 
}
//afficher les arcs 
int afficherArcsGraphe(graphe G){
	if(aucunArc(G)==0){
	 arc* AR ;	
	 AR=G.LA;
	 while(AR!=NULL)	{
	 printf("(%d,%d,%d)",AR->s->info ,AR->d->info,AR->val);
	  AR=AR->suc ; }
	 return 1 ; }
	 else
	 return 0;
}
//chercher un noeud dans la liste 
noeud* chercher( int Ninfo,listeNoeuds *LN ){
	noeud *n;
	n=*LN;
	while(n!=NULL){
  	 if(n->info==Ninfo)
  	  return n;
  	  n=n->suc;
}
return NULL ;
}
//inserer un noeud dans la liste des noeuds
noeud* insererNoeud(int Ninfo,listeNoeuds *LN){
    if(*LN == NULL){
		noeud *n;
        n = creerNoeud(Ninfo); 
        *LN = n;
	    return *LN;
  }
   else{
     noeud *nf;
     nf = *LN;

	while(nf != NULL){	
		if(Ninfo == nf->info){
			return nf;
		}
		if(nf->suc == NULL)
		   break; 
		nf=nf->suc;
	}
	
	noeud *n;
    n = creerNoeud(Ninfo); 
    	nf->suc = n;
	    return n;
	    }
	    	
		   
} 

//chercher arc dans la liste
arc* chercher(noeud *NS,noeud *ND , float v , listeArcs *LA){
 arc * A;
 A=*LA;
 while(A!=NULL){
 	if(A->s->info==NS->info && A->d->info==ND->info && A->val==v)
 	return A;
 	A=A->suc ;
 }
return NULL ;
}

// inserer arc dans la liste
arc* insererArc(noeud *NS,noeud *ND , float v , listeArcs *LA){
arc *arc1,*arc2;
	if(*LA == NULL){
	arc2 = creerArc(NS,ND,v);	
	*LA = arc2;
	return *LA;
	}
	
else{
	  arc *af;
      af = *LA;
      while(af != NULL){
			if(af->d->info == ND->info && af->s->info==NS->info){
				return af;
			}
		
		if(af->suc == NULL)
		   break; 
			af=af->suc;
		}
		arc1 = creerArc(NS,ND,v);
		af->suc=arc1;
		return af;
  	         }
}
//inserer noeud dans graphe
noeud* insererNoeudGraphe(int v, graphe* G){
	noeud *n ;
	n=insererNoeud(v,&G->LN);
	return n ;
}
//inserer arc dans graphe
arc* insererArcGraphe(int NS,int ND,float V,graphe *G){
	noeud* A,*B ;
	A=insererNoeudGraphe(NS,G);
	B=insererNoeudGraphe(ND,G);
	return insererArc(A,B ,V ,&G->LA);
	
}
//exist noeud :
int existNoeud(int v, graphe G){
	noeud *n,*m;
	m= chercher(v,&(G.LN));
	if(m!=NULL)
	{
	return 1;}
	return 0;	
}
//exist chemin :
int existChemin(int Sinfo,int Dinfo,graphe G){
if(aucunArc(G)==0){
 arc * A,*B;
  A= G.LA;
  while(A!=NULL){
 	if(A->s->info==Sinfo ){
 		if( A->d->info==Dinfo){
 			return 1;
		 }
		 
		else{
		 	B=A;
		 	Sinfo=A->d->info;
		 	
		 	while(B!=NULL){
		 	
		 		if( B->d->info==Dinfo){
		 			return 1;
				}
 	        B=B->suc;
			}
		}
	}else
		{
				A=A->suc ;	
		}
 	    
	 }}else{
	 	return 0;
	 }
 
 return 0 ;
 } 

int supprimerArc(int Sinfo, int Dinfo, graphe *G){
		arc *a1,*a2;
		a1 = G->LA;
		a2 = G->LA->suc;
		if(Sinfo == a1->s->info && Dinfo == a1->d->info){
			arc *ad;
			ad = a1;
			G->LA = G->LA->suc;
			free(ad);
		}
		else{
		while(a2 != NULL){
			printf("s");
		if(Sinfo == a2->s->info && Dinfo == a2->d->info){
			arc *as;
			as = G->LA->suc;
            G->LA->suc = G->LA->suc->suc; 
        
			free(as);
			return 1;
		}
		if( a2->suc == NULL)
		   break; 
	
		a1 =  a1->suc;
		a2 = a2->suc;
	}
		
		}

	return 0;
}
/**************************************** SUPPRIMER NOEUD *******************************************************/

int supprimerNoeud(int Ninfo , graphe* G){
	if(existNoeud(Ninfo , *G)){
		noeud *n = G->LN;
		int k=0;
		while(n!=NULL){
			if(k==0){
				if(n->info==Ninfo){
					free(n);
					n=NULL;
					return 1;
				}
				k==1;
			}else{
				if(n->suc->info == Ninfo){
					noeud* n2 = n->suc;
					n->suc = n->suc->suc;
					free(n2);
					return 1;
				}
			}
			
			n = n->suc;
		}
	}
	return 0;
}

/**************************************** DEMI DEGRE INTERIEUR *******************************************************/
int demiDegreInterieur(int N,graphe G){
	int k = 0;
	arc *n;
	n = G.LA;
	while (n != NULL){
		if(n->d->info  == N)
		   k++;
	n = n->suc;	   
	}
	
	 return k;
}
/**************************************** DEMI DEGRE EXTERIEUR *******************************************************/
int demiDegreExterieur(int N,graphe G){
	int k = 0;
	arc *n;
	n = G.LA;
	while (n != NULL){
		if(n->s->info  == N)
		   k++;
	n = n->suc;	   
	}
	
	 return k;
}

//inserer noued dijkstra 
void insererNoeudDijkstra(noeud *N,int infoS,listeArcs A,listeDijkstra *L){
  listeArcs Q ;
  listeDijkstra p,R ;
  p=(cheminDijkstra *)malloc(sizeof(cheminDijkstra ));
  p->Dest=N;
  p->Interm=N;
  p->suc=NULL;
  if(N->info==infoS){
  	p->etat=1;
  	p->c=0;
  }	
  else {
  	p->etat = 0;
  	p->c = INFINITY;
  }
  Q=A;
  while(Q!=NULL && (Q->s->info!=infoS || Q->d!=N ))	 
	Q=Q->suc ;
  if(Q!=NULL){
  	p->Interm=Q->s ;
  	p->c=Q->val;
  }
  if(*L==NULL) *L=p;
  else {
  	R=*L;
  	while(R->suc!=NULL)
  	R=R->suc ;
  	R->suc=p; 
  } 
}
//compter noeuds dans graphe 
int compterNoeud(graphe G){
int K=0;
Noeud* N = G.LN ;
while(N!=NULL){
	if(existNoeud(N->info,G)==1){
	K++; 
	}
	N=N->suc;

}	return K;
}
arc* existeArc(int NS, int ND , graphe G){
 arc * A;
 A=G.LA;
 while(A!=NULL){
 	if(A->s->info==NS && A->d->info==ND)
 	return A;
 	A=A->suc ;
 }
return NULL ;
}

// Dijkstra
void Dijkstra(graphe G,int infos,listeDijkstra *L){
	Noeud *N,*F;
	int n,X=1,j;
	arc * A,*J,*W;
	N=G.LN;
	int min;
	int M=compterNoeud(G);
	listeDijkstra P,K;
		P=(cheminDijkstra *)malloc(sizeof(cheminDijkstra ));
		K=(cheminDijkstra *)malloc(sizeof(cheminDijkstra ));
		W=G.LA;
	while(N!=NULL){
		insererNoeudDijkstra(N,infos,W,L);
		N=N->suc;	
	}
	
do{  
   	   	P=*L;
     	min=INFINITY ;
		while(P!=NULL){
			if(P->etat==0){
			
			
				if(P->c < min){
				
					min=P->c;
					n=P->Dest->info;
					F=P->Dest;
					
				}
			P=P->suc;	
			}
			else P=P->suc;		
		}
		//mise a jour
	   K=*L;
	   while(K!=NULL){
	   	if(K->Dest==F)
	      {
		   K->etat=1;
        	} 	
        	
		else if(K->etat==0){
    	J=existeArc(F->info,K->Dest->info,G);
	
	     if((J!=NULL) && ( min + J->val < K->c)){
	              K->c = min + J->val ;
	        	  K->Interm=F;
		 }
		 else  {
	   		K->Interm=K->Interm;
	   	     K->c=K->c;
	   }
  
	}      
	               //printf("%d  ",K->etat);
			     	K=K->suc;
							
} 	
     //printf("\n");
     X++;
}while(M!=X);  


	

     
}

//afficher Djikstra
void afficherDjikstra(int infos, int infoD, listeDijkstra L){
    listeDijkstra P;

    
		 int t[100] ;
		 int cout[100];
		 int i=0,j;
		
	P=(cheminDijkstra *)malloc(sizeof(cheminDijkstra )); 
    int n=infoD,k;
    
   
    printf("le chemin optimal trouve est le suivant : ",infos,infoD);
     do{
     	P=L;
     	
     
     	while(P!=NULL){
     		 if(P->Dest->info==n){
	
				t[i] = P->Dest->info;
				cout[i] = P->c;
				i++;
				
		
        
	         n = P->Interm->info;
				}	
			P=P->suc;
		 }	
		 
		
	    if(n==infos){	
      
	        	k=0;
	        
	        	
	        	printf("%d ---->", n);
				for(j=i-1;j>=0;j--){
				
				printf("%d ( %d )",t[j],cout[j]);
				if(j==0)
				{	
				
				printf("\n\n\nla valeur de chemin est : %d",cout[j]);
					
					break;
				}
				
					
					
				printf("---->");
				}
				
				
			
	              }	 	 	
	   else
	   	k++ ; 	   	
} while(k!=0);

}

void fichierGraphe(const char *s,graphe *G){
	FILE *f;
	int a,c,aa,bb;
	float cc;
	char buffer[100];
	f=fopen(s,"r");
	if(f==NULL)
	printf("fichier n'existe pas .");
	else {
		a=fgetc(f);
		while(a!='\n'){
			//printf("%c",a);
			a=a-48;
			insererNoeudGraphe(a,G);
			a=fgetc(f);
		}
		printf("\n");
		while(fgets(buffer,100,f)!=NULL){
			sscanf(buffer,"%d%d%f ",&aa,&bb,&cc);
			printf("%d \t %d \t %f \n",aa,bb,cc);
			insererArcGraphe(aa,bb,cc,G);
		}
	}
	fclose(f);
}

main(){
	
	int  j ;
	int source;
	int destination ;
	graphe G ;
	G=creerGraphe();
    listeDijkstra L[20];
    Noeud* N ;
    arc* A ;
    const char *s="C:/Users/hamza/Desktop/RO-devoir-dijkstra/fichier.txt";
    printf("liste de adjacence de notre graphe est : \n");
	fichierGraphe(s,&G); 
	printf("\ndonner le sommet source : ");
	scanf("%d",&source);
	printf("\ndonner le sommet destination : ");
	scanf("%d",&destination);
	if(!existChemin(source,destination,G))
	{
	printf("\n\nil ne existe pas de chemin entre le sommet %d et destination %d  \n\n\n",source,destination);
	}
	else
	{

    Dijkstra(G,source,L);
    printf("\n");
    
    
    afficherDjikstra(source,destination,*L);
    printf("\n\n\n\n");
    }
	system("pause");
	
}


