#include<iostream>
#include <limits.h>
#include <iomanip>
using namespace std;

#define V 6
int Graph[V][V];
int parent[V];
string restaurant[V] = {"Restaurant", "Hostel City     ", "Faizabad         ", "Taramri         ", "Khannapull      ", "Commercial Market" };

struct node
{
    string foodname;
    int quantity;   float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct rider{
	string name;
	int id;
	rider* next = NULL;
	node* order = NULL;
};

struct customerRecord{
	int id;
	string name;
	string phno;
	struct customerRecord* left = NULL;
	struct customerRecord* right = NULL;
	
};

struct node *fMenuItems = NULL, *lMenuItems = NULL;
struct node *fCustomerOrder = NULL,*lCustomerOrder = NULL;
struct node *sales;

struct rider *fRider = NULL, *lRider = NULL; 
struct customerRecord* root = NULL;

void addRider(string name,int id){
	rider* temp = new rider;

	temp->name=name;
	temp->id = id;
	
	
	if(fRider == NULL){
		fRider = lRider = temp;
	}
	else{
		lRider->next = temp;
		lRider = temp;
	}
	
	
	
}


void insertCustomerRecord(string name,int id,string ph){
	customerRecord *cRecord=new customerRecord;

	


 	cRecord->id=id;
 	cRecord->name = name;
 	cRecord->phno = ph;
	cRecord->left = NULL;
 	cRecord->right = NULL;
 	
 	
 	if (root==NULL){
 		root=cRecord;
	 }
	 else{
	 	
	 	customerRecord *p=root, *q;
	
	 	
	 	while(p!=NULL){
	 		q=p;
	 		
	 		if(cRecord->id>q->id){
	 			p=p->right;
	 			
			 }
			 
			 else{
			 	p=p->left;
			 }
	 }
	 if(cRecord->id>q->id){
	 	q->right=cRecord;
	 }
	 else if(cRecord->id<q->id){
	 	q->left=cRecord;
	 }
 }
}




void displayCustomerRecord(struct customerRecord *root) {
 
  
  if (root != NULL) {
  	cout<<endl;
    displayCustomerRecord(root->left);
    cout<<endl;
    cout <<"Customer ID: " <<root->id <<endl;
    cout<<"Customer Name: "<<root->name<<endl;
    cout<<"Phone no: "<<root->phno<<endl;;

    
    cout<<endl;
    displayCustomerRecord(root->right);
    if(root==NULL){
    	return;
	}
  }

}

void adminmenu()
{
    cout<<"\n1. View total sales\n";
    cout<<"\n2. Add new items in the order menu\n";
    cout<<"\n3. Delete items from the order menu\n";
    cout<<"\n4. Display order MENU\n";
    cout<<"\n5. Display Customer Records\n";
    cout<<"\n6. Back To Main Menu \n\n";
    cout<<"\t   Enter Your Choice :";
}

void customermenu()
{
    cout<<"\n1. Place your order\n";
    cout<<"\n2. View your ordered items\n";
    cout<<"\n3. CHECKOUT\n";
    cout<<"\n4. Back To Main Menu \n\n";
    cout<<"  Enter Your Choice: ";
}

struct node* createadmin(struct node *head,int data, string foodname, float price)
{
    struct node* menu = new node;
	
    menu->data = data;
    menu->price = price;
    menu-> quantity = 0;
    menu->foodname = foodname;
    menu->next = NULL;
    menu->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        fMenuItems = lMenuItems = menu;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=menu;
        menu->prev = lMenuItems;
        lMenuItems = menu;
    }

    return fMenuItems;
}

struct node* createcustomer(struct node *head,int data,int quantity,string name,int id,string phno)
{
    struct node* cart = new node;
	struct node* deliveryOrder = new node;
	struct rider* tempRider = fRider;
	
	string n = name;
	int i = id;
	string ph = phno;
	

    struct node *temp1 = fMenuItems;
    int check = 0;
    while(temp1!=NULL){	
        if(temp1->data==data)
        {
            check = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(check==1 && data!= 0)
    {
        cart->data = data;
        cart->price = quantity*(temp1->price);
        cart-> quantity = quantity;
        cart->foodname = temp1->foodname;
        cart->next = NULL;
        cart->prev = NULL;

        struct node *temp = head;

        if(temp==NULL){
        	fCustomerOrder->next = lCustomerOrder = cart;
		}
        else
        {
            while(temp->next!=NULL){
			
            	temp=temp->next;
		}
                

            temp->next=cart;
            cart->prev = lCustomerOrder;
            lCustomerOrder = cart;
        
        //riderorder details
        deliveryOrder->data = cart->data;
        deliveryOrder->price = cart->price;
        deliveryOrder->quantity = cart->quantity;
        deliveryOrder->foodname = cart->foodname;
        if(tempRider->order == NULL){
        	tempRider->order = deliveryOrder;

	}
		else if(tempRider->order!=NULL){
		 	deliveryOrder->next=tempRider->order;
			tempRider->order = deliveryOrder;
			
		}
		
		insertCustomerRecord(n,i,ph);

		
    
	}
}
    else
    {
        cout<<"\n\t\t\t\t\t\t\tThis item is not present in the menu!\n";
    }
    return fCustomerOrder;
}

void DisplayRiderDetails(){
	rider *p=fRider;
	cout<<"\t\tSATTI RIDER DETAILS"<<endl<<endl;
	while(p!=NULL){
		cout<<"\tID:"<<p->id<<"\tRider: "<<p->name<<endl;
		if(p->order==NULL){
		cout<<"NO FOOD TO BE DELIVERED";
	}
		cout<<"\t\tORDER DETAILS"<<endl;
		while(p->order!=NULL){
		
			cout<<" "<<endl;
		cout<<"  "<<"\t  Item"<<"\t\t Qty"<<"\t\t Amount"<<endl;
		cout<<"  "<<p->order->foodname<<"\t\t  "<<p->order->quantity<<"\t\t  "<<p->order->price<<endl;
        
        p->order=p->order->next;
			
		}
		p=p->next;
	}
}



void displayList(struct node *head)
{
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        cout<<"\n LIST is EMPTY!!\n\n";
    }
    else
    {
        cout<<"\n";
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
                cout<<temp1->data<<" - "<<temp1->foodname<<"\t"<<temp1->price<<endl;
            else
            {
                cout<<temp1->data<<" - "<<temp1->foodname<<"\t"<<temp1->quantity<<"\t"<<temp1->price<<endl;
            }

            temp1 = temp1->next;
        }
        cout<<"\n";
    }

}

struct node* totalsales(int data,int quantity)
{
    struct node* getSales = new node;
    int check = 0;

    struct node *temp1 = fMenuItems;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    getSales->data = data;
    getSales->price = quantity*(temp1->price);
    getSales-> quantity = quantity;
    getSales->foodname = temp1->foodname;
    getSales->next = NULL;
    getSales->prev = NULL;

    struct node *temp = sales;

    if(temp==NULL)
        sales = getSales;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                check = 1;
                break;
            }
            temp=temp->next;
        }

        if(check==1)
        {
            temp->quantity += getSales-> quantity;
            temp->price += getSales->price;
        }
        else
        {
            temp->next=getSales;
        }
    }

    return sales;
}

void calculatetotsales()
{
    struct node *temp = fCustomerOrder;
    while(temp!=NULL)
    {
        sales = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* deletea(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        cout<<"\n\t\t\t\t\t\t\tList is empty\n";
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            delete(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            delete(temp);
        }
    }
    return head;
}

int deleteadmin()
{
    cout<<"\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin>>num;

    struct node* temp=fMenuItems;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            fMenuItems = deletea(num, fMenuItems, lMenuItems);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}


void displaybill()
{
    displayList(fCustomerOrder);
    struct node *temp = fCustomerOrder;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    cout<<"\t\t\t\t\t\t\tTotal price: "<<total_price<<"\n";

}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            delete(temp->prev);
        }
        delete(temp);
        head = NULL;
    }

    return head;
}

void addItem(){
			cout<<"\n\t\t\t\t\t\t\tEnter id of the food item: ";
			struct node *temp = fMenuItems;
			int num,check = 0;
			string name;
			float price;
            cin>>num;

            

            while(temp!=NULL)
            {
                if(temp->data==num)
                {
                    cout<<"\n\t\t\t\t\t\tFood item with provided serial number already exists!\n\n";
                    check = 1;
                    break;
                }
                temp = temp->next;
                
				}
                if(check==1){
                	return;
            }
 
            

            cout<<"\t\t\t\t\t\t\tEnter food name: ";
            cin.ignore();
			getline(cin,name);
            cout<<"\t\t\t\t\t\t\tEnter price: ";
            cin>>price;
            fMenuItems = createadmin(fMenuItems, num, name, price);
            cout<<"\n\t\t\t\t\t\t\tNew food item added to the menu!\n\n";
}

void admin()
{
    cout<<"\n\t\t\t\t\t   ----------------------------------------------\n";
    cout<<"\t\t\t\t\t\t      A D M I N  P A N E L\n";
    cout<<"\t\t\t\t\t   ----------------------------------------------\n";
    string name;
    float price;
    struct node *temp = fMenuItems;
    while(1)
    {
        adminmenu();

        int opt;
        cin>>opt;

        if(opt==6)
            break;

        switch (opt)
        {
        case 1:
            displayList(sales);
            break;
        case 2:
        	addItem();
            break;
        case 3:
            if(deleteadmin())
            {
                cout<<"\n\t\t\t\t\t\t Updated MENU \n";
                displayList(fMenuItems);
            }
            else
                cout<<"\n\t\t\t\t\t\tFood item with ENTERED ID number does not exist!\n\n";

            break;
        case 4:
            cout<<"\n\t\t\t\t\t\t\t    MENU CARD \n";
            displayList(fMenuItems);
            break;
        case 5:
        	cout<<"\t\t\t\t\t\t\t\t    CUSTOMER RECORDS\n";
        	displayCustomerRecord(root);
        	break;
        default:
            cout<<"\nInvalid Selection!PLease choose a valid option\n";
            break;
        }
    }
}







void insertRestaurant(int va, int vb, double distancebtwpnts) {
    Graph[va][vb] = distancebtwpnts;
    Graph[vb][va] = distancebtwpnts;
}


void printPath(int parent[], int j)
{
	
	// Base Case : If j is source
	if (parent[j] == - 1)
		return;
	printPath(parent, parent[j]);
	cout<<"->"<<restaurant[j];
}
int minDistance(int distance[],
	bool visit[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (visit[v] == false &&
				distance[v] <= min)
			min = distance[v], min_index = v;

	return min_index;
}

void dijkstra(int Graph[V][V])
{
	int src=0;
	int dist[V];
	bool visited[V];

	for (int i = 0; i < V; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX;
		visited[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++)
	{
		
		int u = minDistance(dist, visited);

		visited[u] = true;

		for (int v = 0; v < V; v++)

			if (!visited[v] && Graph[u][v] &&
				dist[u] + Graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + Graph[u][v];
			}
	}

	cout<<endl;
	for(int i=1; i<V; i++)
	{
			
        cout<<"Restaurant -> "<<restaurant[i]<<setw(6)<<dist[i]<<"km"<<endl;
        
    }
}
	
	
	
	
	
	
	
void HomeDelivery(){
		cout
                << "*********************************************************************************************************"
                <<"																										"<<endl;
		cout<<  "																										        "<<endl;
        cout <<"                                   FOOD DELIVERY 														        " << endl;
		cout<<"    																										    "<<endl;
        cout
                << "*********************************************************************************************************"
                << endl;
       cout<<endl;
		cout<< "                                   Available Food Delivery Locations     "<<endl;
		cout<<endl;
		cout
                << "*********************************************************************************************************"
                << endl;
		cout<<"\n1. Hostel City";
		cout<<"\n2. Faizabad";
		cout<<"\n3. Taramri";
		cout<<"\n4. Khannapull";
		cout<<"\n5. Commercial Market"<<endl;
		
		
		
		//initializing 2d array and assigning every edge 0
		for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    Graph[i][j] = 0;

                }

            }
            
            
	   //Restaurant Main
	   insertRestaurant(0, 0, 0);
	   insertRestaurant(0, 3, 3.0);
	   insertRestaurant(0, 1, 1.8);
	   //Hostel City
		insertRestaurant(1, 2, 12.7);
	   //Taramri Chowk
	   insertRestaurant(3, 4, 4.8);
	   //Faizabad
	   insertRestaurant(2, 5, 6.6);
	   //Khannapull
	   insertRestaurant(4, 5, 9.7);
	   cout<<endl;
	           cout
                << "*********************************************************************************************************"
                <<"                                                                                                      "<< endl;
		cout<< "                               Shortest Routes by using DIJKSTRA ALGORYTHM                                 " <<endl;
		cout<<"                                                                                                             "<<endl;
		        cout
                <<"********************************************************************************************************"
                << endl;
	   dijkstra(Graph);
	   cout<<endl;
	   int loc;
	   cout<<"Enter your location: ";
	   cin>>loc;
	   
	   while(loc>5 || loc<1){
	   	cout<<"Invalid! Enter choice again: ";
	   	cin>>loc;
	   }
	   
	   if(loc<=5 && loc!=0){
	           cout
                << "*********************************************************************************************************"
                <<"|																										|"<< endl;
	   cout<< "    |                           Shortest Path to reach your Location    										|" <<endl;
	   cout<<"     |																										|"<<endl;
	        cout
                <<"|********************************************************************************************************|"
                << endl;
       cout<<endl;
	   cout<<"Restaurant\t";
	   printPath(parent, loc);
	   cout<<endl;
	   cout<<endl;
	   }
       
}







void serviceType(){
	int choice;
	cout<<endl;
    cout<<"1. DineIn/TakeAway\n2. Home Delivery";
    cin>>choice;
    while(choice!=1 && choice!=2){
    	cout<<"Invalid! Enter choice again: ";
    	cin>>choice;
	}
	if(choice == 1){
		fCustomerOrder = deleteList(fCustomerOrder);
		fRider->order=NULL;
		cout<<"Cooking! Service in Progress";
		cout<<"..."<<endl;
		cout<<"..."<<endl;
		cout<<"..."<<endl;
		cout<<"Order Served! THANKYOU For Your PATIENCE"<<endl;
	}
	else{
		HomeDelivery();
		fCustomerOrder = deleteList(fCustomerOrder);
		cout<<endl;
		cout<<"Food is being Prepared "<<endl;
		cout<<"..."<<endl;
		cout<<"..."<<endl;
		cout<<"..."<<endl;
		cout<<"Rider has your Order"<<endl;
		DisplayRiderDetails();
		cout<<endl<<endl;
	
		cout<<"Rider is on its way ! Food will be Delivered Soon. "<<endl;
		fRider->order=NULL;
		cout<<"\tFOOD DELIVERED"<<endl<<endl<<endl;
		DisplayRiderDetails();
		
	}
	
	
}



void customer(string name,int id,string phno)
{
	string na = name;
	int i = id;
	string ph = phno;
    cout<<"\n\t\t\t\t\t   ----------------------------------------------\n";
    cout<<"\t\t\t\t\t            C U S T O M E R   P A N E L\n";
    cout<<"\t\t\t\t\t   ----------------------------------------------\n";
    int quantity;
    while(1)
    {
        customermenu();

        int opt;
        cin>>opt;

        if(opt==4)
            break;

        switch (opt)
        {
        case 1:
            displayList(fMenuItems);
            cout<<"\nEnter id of the item to order: ";
            int id;
            cin>>id;
            cout<<"Enter quantity: ";
            cin>>quantity;
           
            	
			
            fCustomerOrder = createcustomer(fCustomerOrder, id, quantity,na,i,ph);
            break;
        case 2:
            cout<<"\n\t\t\t\t\t\t\t  List of ORDERED ITEMS \n";
            displayList(fCustomerOrder);
            break;
      
        case 3:
            calculatetotsales();
            cout<<"\n\t\t\t\t\t\t\t   `-- RECEIPT --` \n";
            displaybill();
            serviceType();
            
            break;

        default:
            cout<<"\n\t\t\t\t\t\tInvalid Selection!PLease choose a valid option\n";
            break;
        }
    }

}
void mainnenu()
{
    cout<<"\n                               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"                               |                    RESTURANT MANAGEMENT SYSTEM              |\n";
    cout<<"                               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
    cout<<"1. ADMIN PANEL\n";
    cout<<"2. CUSTOMER PANEL\n";
    cout<<"3. Exit\n\n";
    cout<<"Enter your choice: ";
}












int main()
{	

	string name;
	int id;
	string phno;
	addRider("Aizaz",123);
	struct node* temp = new node;
	temp->data = 0;
	temp->foodname = "------------------------------------------------------------------------]";
	temp->price = 0;
	temp->quantity =0;
	
	fCustomerOrder=temp;
	fMenuItems = createadmin(fMenuItems,0,"----------------------------------------------------------------",0000000);
    fMenuItems = createadmin(fMenuItems,1,"BIRYANI",200);
    fMenuItems = createadmin(fMenuItems,2,"PIZZA",1200);
    fMenuItems = createadmin(fMenuItems,3,"BURGER",180);
    fMenuItems = createadmin(fMenuItems,4,"PASTA",320);
    fMenuItems = createadmin(fMenuItems,5,"FRENCH-FRIES",150);

    while(1)
    {
        mainnenu();
        int choice;
        cin>>choice;

        if(choice==3)
        {
            cout<<"\n\n\t\t\t\t\t THANK YOU\n";
            break;
        }

        switch (choice)
        {
        case 1:
            admin();
            break;
        case 2:
			cout<<"Enter Customer Name: ";
			cin>>name;
			cout<<"Enter id: ";
			cin>>id;
			cout<<"Enter Phone Number: ";
			cin>>phno;
            customer(name,id,phno);
            break;
        case 3:
            break;

        default:
            cout<<"\n\t\t\t\t\t\tInvalid Selection!PLease choose a valid option\n";
            break;
        }
    }
}


