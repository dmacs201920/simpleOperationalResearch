/*                                     AUM SRI SAI RAM
  Purpose:
  Written on:
  Written by:
*/

#include "Trans_Header.h"

static int M,N;
static int nbasic,count=0;
node* newNode(int d,int r,int c) {
  node* temp;
  temp=(node *) malloc(sizeof(node));
  temp->cost = d;
  temp->right = temp->down = NULL;
  temp->quantity =0;
  temp->basic=0;
  temp->coeff=0;
  temp->r=r;
  temp->c=c;
  return temp;
}

node* constructTableu(int m, int n) {
  int data,k=0,i,j;
  node* mainhead = NULL;
  node* head[m+2];
  node *righttemp, *newptr;
  node *temp1,*temp2;
  M=m,N=n;
  nbasic=M*N-(M+N-1);
  int balancecheck[M+N];

  for (i = 0; i <= m; i++) {
    head[i] = NULL;
    for ( j = 0; j <= n; j++) {

      if(i==m && j==n)
	break;
      
      if(i<m){
	if(j<n){
	  fscanf(f,"%d",&data);
	  fgetc(f);
	}
	else{
	  fgetc(f);
	  fscanf(f,"%d",&data);
	  fgetc(f);
	  balancecheck[k++]=data;
	}
      }
      else{
	fscanf(f,"%d",&data);
	fgetc(f);
	balancecheck[k++]=data;
      }

      newptr = newNode(data,i,j);
      if (!mainhead)
	mainhead = newptr;
      if (!head[i])
	head[i] = newptr;
      else
	righttemp->right = newptr;
      righttemp = newptr;
    }
    if(i!=m)
      righttemp->right=newNode(data,-1,-1);
  }
  head[m+1]=newNode(head[m]->cost,-1,-1);
  temp1=head[m];
  temp2=head[m+1];
  temp1=temp1->right;
  while(temp1){
    temp2->right=newNode(temp1->cost,-1,-1);
    temp2=temp2->right;
    temp1=temp1->right;
  }
  for (int i = 0; i <= m ; i++) {
    temp1 = head[i];
    temp2 = head[i + 1];
    while (temp1 && temp2) {
      temp1->down = temp2;
      temp1 = temp1->right;
      temp2 = temp2->right;
    }
  }
  BalanceTableau(balancecheck,&M,&N,mainhead);
  return mainhead;
}

void BalanceTableau(int *array,int *M,int *N,node *head){
  int i, j, k, sum=0, count;
  node *temp, *temp0=NULL, *temp1, *def, *def1, *head1;
  for (i=0; i<*M; i++)
    sum+=array[i];
  for (j=*M; j<*N+*M; j++)
    sum-=array[j];
  if (sum>0){
    i=0, j=*N;
    def=head;
    for(k=1;k<*N;k++)
      def=def->right;
    while(i<*M){
      temp=newNode(0,i,j);
      temp1=def->right;
      def->right=temp;
      temp->right=temp1;
      i++;
      def=def->down;
      if(temp0==NULL)
        temp0=temp;
      else{
	temp0->down=temp;
	temp0=temp;
      }
    }
    count=0;
    def1=def;
    while(count<2){
      temp=newNode(sum,-1,-1);
      temp0->down=temp;
      temp0=temp;
      temp->right=def1->right;
      def1->right=temp;
      def1=def1->down;
      count++;
    }
    *N=*N+1;
  }
  else if (sum<0){
    i=*M, j=0;
    def=head;
    for(k=1;k<*M;k++)
      def=def->down;
    while(j<*N){
      temp=newNode(0,i,j);
      temp1=def->down;
      def->down=temp;
      temp->down=temp1;
      j++;
      def=def->right;
      if(temp0==NULL)
        temp0=temp;
      else{
	temp0->right=temp;
	temp0=temp;
      }
    }
    count=0;
    def1=def;
    while(count<2){
      temp=newNode(0-sum,-1,-1);
      printf("Re..\n");
      temp0->right=temp;
      temp0=temp;
      temp->down=def1->down;
      def1->down=temp;
      def1=def1->right;
      count++;
    }
    *M=*M+1;
  }
}

void display(node* head) {
  node *rp, *dp = head;
  int i,j;
  char *mes;
  nl(70);
  mes="Tableau";
  fprintf(f,"%s %d:\n",mes,count);
  printf("%s %d:\n",mes,count);
  count++;
  for(i=0;i<M;i++) {
    rp = dp;
    for(j=0;j<N;j++) {
      if(rp==NULL) break;
      fprintf(f,"|%3d  %3d  %3d",rp->quantity,rp->cost,rp->basic);
      printf("|%3d  %3d  %3d",rp->quantity,rp->cost,rp->basic);
      rp = rp->right;
    }
    dp = dp->down;
    printf("\n");
    fprintf(f,"\n");
  }
  nl(70);
}

void initialiseNW(node *head){
  node *p = head;int i=1,j=1,r=0;
  while(p->right->right!=NULL && p->down->down!=NULL) {
    r=enterQuan(p,i,j);
    if(r==0)
      i++,p->basic=1,p=p->down;
    else
      j++,p->basic=1,p=p->right;
  }
}

int enterQuan(node *n,int r, int c){
  int i=1,j=1,q=0,rs=0;
  int dem=0,sup=0;
  node *d=n , *s=n;
  while(d->down!=NULL)
    d=d->down;
  while(s->right!=NULL)
    s=s->right;
  if(d->cost > s->cost){
    q=s->cost;
    rs=0;
  }
  else{
    q=d->cost;
    rs=1;
  }
  n->quantity=q;
  s->cost-=q;
  d->cost-=q;
  return rs;
}

void iter_nFindSol(node *head){
  int dum[M+N],ind[M+N],
    i,j,t,d,q=0,count=1;
  nonbasic *h1=NULL,*temp1;
  clos_path *h2=NULL,*h3=NULL,*h4=NULL,*temp2;
  node *k=head,*l=head;
  node *ent=NULL,*leav=NULL;
  while(1){
    Initialise(dum,ind,M+N);
    h1=NULL,h2=NULL,h3=NULL,i=0,t=1;
    dum[0]=0,ind[0]=0;
    
    for(k=head; k->down->down!=NULL; k=k->down)
      for(l=k; l->right->right!=NULL; l=l->right){
	if(l->basic==1)
	  h3=addNodeCl(l,h3,1);
      }
    while(h3!=NULL){
      i=0;
      for(k=head; k->down->down!=NULL; k=k->down){
	j=M;
	for(l=k; l->right->right!=NULL; l=l->right){
	  if(l->basic==1){
	    if(findNode(l,h3)){
	      d=findNum(ind,i,j);
	      if(d==i){
		dum[j]=l->cost-dum[i];
		ind[t]=j;
		t++;
		h3=delNodeCl(l,h3);
		h2=addNodeCl(l,h2,1);
	      }
	      else if(d==j){
		dum[i]=l->cost-dum[j];
		ind[t]=i;
		t++;
		h3=delNodeCl(l,h3);
		h2=addNodeCl(l,h2,1);
	      }
	    }
	  }
	  j++;
	}
	i++;
      }
    }

    i=0,j=0,t=0;
    for(k=head; k->down->down!=NULL; k=k->down){
      j=M;
      for(l=k; l->right->right!=NULL; l=l->right){
	if(l->basic==0){
	  l->coeff=dum[i]+dum[j]-l->cost;
	  h1=addNonb(l,h1);
	}
	j++;
      }
      i++;
    }
  
    ent=findEnt(h1);
    if(ent==NULL){
      displayAns(head);
      exit(0);
    }
    
    if(ent!=NULL){
      findLeav(h2,ent,head);
      display(head);
    }
    q++;
    while(h1!=NULL){
      temp1=h1;
      h1=h1->next;
      free(temp1);
    }
    printf("\n"),fprintf(f,"\n");
    if(ent==NULL) break;
  }
}

int findNum(int a[M+N],int i,int j){
  int k=0;
  if(i<0 && j<0){
    while(k<M+N)
      if(a[k]==i)
	return k;
    return 0;
  }
  while(k<M+N){
    if(a[k]==i || a[k]==j)
      return a[k];
    else
      k++;
  }
  return -1;
}

void Initialise(int *A,int *B,int n){
  int i;
  for(i=0;i<n;i++){
    A[i]=-99999;
    B[i]=99999;
  }
}

int findNode(node *h,clos_path *h3){
  clos_path *t=h3;
  if(t==NULL) return 0;
  while(t!=NULL){
    if(t->var==h)
      return 1;
    t=t->next;
  }
  return 0;
}

nonbasic* addNonb(node *g,nonbasic *head){
  nonbasic *temp=head, *t;
  t=(nonbasic *) malloc(sizeof(nonbasic));
  t->var=g;
  t->next=NULL;
  if(temp==NULL) return t;
  while(temp->next!=NULL)
    temp=temp->next;
  temp->next=t;
  return head;
}

clos_path* addNodeCl(node *g,clos_path *head,int p){
  clos_path *temp=head, *t1=NULL;
  clos_path *p1=head;
  
  t1=(clos_path *) malloc(sizeof(clos_path));
  t1->var=g;
  t1->next=NULL;
  
  if(temp==NULL) return t1;
  if(p==1){
    while(temp->next!=NULL)
      temp=temp->next;
    temp->next=t1;
  }
  else{
    t1->next=head;
    head=t1;
  }

  p1=head;
  return head;
}

node *findEnt(nonbasic *h){
  int max=0;
  nonbasic *t=h;
  node *temp=NULL;
  while(t!=NULL){
    if(max < t->var->coeff){
      max=t->var->coeff;
      temp=t->var;
    }
    t->var->coeff=0;
    t=t->next;
  }
  if(temp!=NULL){
    temp->basic=1;
  }
  return temp;
}

void findLeav(clos_path *h,node *ent, node *head){ 
  clos_path *h1=h, *h2=NULL, *h3, *h4;
  node *temp=NULL, *leav=NULL;
  int t, redc, low_quant=9999999;
  int plus, k, i=0;
  
  h1=addNodeCl(ent,h1,0);
  
  h2=h1;
  
  while(h2!=NULL){
    h1=findNbrs(&(h2->var),h1,-1),h2=h2->next;
    /*
    clos_path *p1=h1;
    while(p1!=NULL)
    {
      printf("|%3d  %3d  %p   %p\n",p1->var->cost,p1->var->quantity,p1->var, p1);
      p1=p1->next;
    }
    printf("LLLLLLLLLLLLLLL\n");
    */
  }
  h=h1;
  
  temp=ent;
  h3=h,h1=h3,h4=h3;
  t=0;
  while(h3!=NULL){
    h4=h1;
    while(h4->var!=temp)
      h4=h4->next;
    h4->var=h3->var;
    h3->var=temp;
    findNbrs(&temp,h,t%2);
    h3=h3->next;
    t++;
  }
  
  h3=h;
  plus=1;
  redc=0;
  while(h3!=NULL){
    if(!plus)
      if(h3->var->quantity<low_quant)
	low_quant=h3->var->quantity;
    h3=h3->next,plus=!plus;
  }
  if(low_quant==0){
    ent->basic=0;
    displayAns(head);
    exit(1);
  }
    
  if(h!=NULL){
    plus=1,h2=h,k=0;
    while(h2!=NULL){
      h2->var->quantity += plus ? low_quant : -low_quant;
      if(k==0)
	if(h2->var->quantity == 0){
	  leav=h2->var;
	  k++;
	  h2->var->basic=0;
	}
      h2=h2->next;
      plus=!plus;
    }
  }

  while(h!=NULL){
    clos_path *temp2=h;
    h=h->next;
    free(temp2);
  }
}

clos_path* findNbrs(node **t,clos_path *h,int c){
  node *nbr[2]={NULL,NULL}, *temp=NULL;
  clos_path *h1=h;
  int k=0;
  while(h1!=NULL){
    if(*t!=h1->var){
      if((*t)->r==h1->var->r && nbr[0]==NULL)
	nbr[0]=h1->var;
      else if((*t)->c==h1->var->c && nbr[1]==NULL)
	nbr[1]=h1->var;
      if(nbr[0]!=NULL && nbr[1]!=NULL){
	break;
      }
    }
    h1=h1->next;
  }
  if(c==-1){
    if(nbr[0]==NULL || nbr[1]==NULL) 
      h=delNodeCl(*t,h);
    return h;
  }
  else{
    temp=*t;
    *t=nbr[c];
    return NULL;
  }
}

clos_path* delNodeCl(node *h3,clos_path *h){
  clos_path *temp, *t=h;
  if(t->var!=h3){
    if(t->next!=NULL){
      while(t->next->var!=h3)
	t=t->next;
      temp=t->next;
      t->next=t->next->next;
    }
    else
      h=NULL;
    free(temp);
  }
  else{
    temp=h;
    h=h->next;
    free(temp);
  }
  return h;
}

void displayAns(node *head){
  fprintf(f,"\nFinal Solution\n");
  printf("\nFinal Solution\n");
  node *rp, *dp = head;
  int i, j, totalcost=0;
  char ch='A',sp=' ';int s=1;
  nl(70);
  putchar('\n');
  fputc('\n',f);
  printf("%6c",sp);
  fprintf(f,"%6c",sp);
  for(j=0;j<N;j++){
    printf("|%3d  ", s);
    fprintf(f,"|%3d  ", s++);
  }
  putchar('\n');
  fputc('\n',f);
  printf("%6c",sp);
  fprintf(f,"%6c",sp);
  nl(N*6);
  for(i=0;i<M;i++) {
    printf("|%3c  ", ch);
    fprintf(f,"|%3c  ", ch++);
    rp = dp;
    for(j=0;j<N;j++) {
      if(rp==NULL) break;
      if(rp->basic==1){
	printf("|%3d  ",rp->quantity);
	fprintf(f,"|%3d  ",rp->quantity);
	totalcost += rp->quantity * rp->cost;
      }
      else{
	printf("| -   ");
	fprintf(f,"| -   ");
      }
      rp = rp->right;
    }
    dp = dp->down;
    fprintf(f,"\n");
    printf("\n");
  }
  nl(70);
  fprintf(f,"\nTotal cost:%d\n\n",totalcost);
  printf("\nTotal cost:%d\n\n",totalcost);
}

void nl(int k)
{
  int j;
  for(j=0;j<k;j++){ 
    fputc('-',f);
    putchar('-');
  }
  putchar('\n');
  fputc('\n',f);
}

