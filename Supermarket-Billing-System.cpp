#include<iostream>
#include<fstream>
using namespace std;

class Shopping{
    private:
        int pcode;
        float price;
        float dis;
        string pname;

    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
};

void Shopping :: menu(){
    m:
    int choice;
    string email;
    string password;

    cout<<"\t\t\t\t____________________________\n";
    cout<<"\t\t\t\t                            \n";
    cout<<"\t\t\t\t    Supermarket Main Menu   \n";
    cout<<"\t\t\t\t____________________________\n";
    cout<<"\t\t\t\t|  1) Administrator        |\n";
    cout<<"\t\t\t\t|                          |\n";
    cout<<"\t\t\t\t|  2) Buyer                |\n";
    cout<<"\t\t\t\t|                          |\n";
    cout<<"\t\t\t\t|  3) Exit                 |\n";
    cout<<"\t\t\t\t|                          |\n";
    cout<<"\n\t\t\t\tPlease select!\n\t\t\t\t";
    cin>>choice;

    switch(choice){
        case 1:
            cout<<"\t\t\tPlease Login \n";
            cout<<"\t\t\tEnter Email \n\t\t\t";
            cin>>email;
            cout<<"\t\t\tEnter password \n\t\t\t";
            cin>>password;

            if(email=="suneha@gmail.com" && password=="suneha21"){
                administrator();
            }
            else{
                cout<<"\t\t\tInvalid Email/Password";
            }
            break;

        case 2:
            buyer();

        case 3:
            exit(0);

        default:
            cout<<"\t\t\tPlease select from given options";
    }

    goto m; //goes back to main menu
}

void Shopping :: administrator(){
    m:
    int choice;

    cout<<"\n\n\n\t\t\t Administrator menu";
    cout<<"\n\t\t\t|____1) Add the product____|";
    cout<<"\n\t\t\t|                          |";
    cout<<"\n\t\t\t|____2) Modify the product_|";
    cout<<"\n\t\t\t|                          |";
    cout<<"\n\t\t\t|____3) Delete the product_|";
    cout<<"\n\t\t\t|                          |";
    cout<<"\n\t\t\t|____4) Back to main menu__|";

    cout<<"\n\n\t\t\tPlease enter your choice\n\t\t\t";
    cin>>choice;

    switch(choice){
        case 1: 
            add();
            break;

        case 2:
            edit();
            break;

        case 3:
            rem();
            break;

        case 4:
            menu();
            break;

        default:
            cout<<"\n\t\tInvalid Choice!";
    }
    goto m;
}

void Shopping :: buyer(){
    m:
    int choice;

    cout<<"\t\t\t___________________\n";
    cout<<"\t\t\t                   \n";
    cout<<"\t\t\t       Buyer       \n";
    cout<<"\t\t\t___________________\n";
    cout<<"                         \n";
    cout<<"\t\t\t 1) Buy Product    \n";
    cout<<"                         \n";
    cout<<"\t\t\t 2) Go Back        \n";

    cout<<"\t\t\t Enter your choice : ";
    cin>>choice;

    switch(choice){
        case 1:
            receipt();
            break;

        case 2:
            menu();
            break;

        default:
            cout<<"Invalid Choice";
    }
    goto m;

}

void Shopping :: add(){
    m:
    fstream data;
    int c, token = 0;
    float p, d;
    string n;

    cout<<"\n\n\t\t\t Add new product";
    cout<<"\n\n\t\tProduct code: ";
    cin>>pcode;
    cout<<"\n\n\t\tName of product: ";
    cin>>pname;
    cout<<"\n\n\t\tPrice of product: ";
    cin>>price;
    cout<<"\n\n\t\tDiscount on product: ";
    cin>>dis;

    data.open("database.txt", ios::in);

    if(!data){
        data.open("database.txt", ios::app|ios::out);
        data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
        data.close();
    }
    else{
        data>>c>>n>>p>>d;

        while(!data.eof()){
            if(c == pcode){     //duplicate product entered 

                cout<<"\t\tDuplicate product entered!";
                token++;
            }
            data>>c>>n>>p>>d;
        }
        data.close();

        if(token == 1){
            goto m;
        }
        else{
            data.open("database.txt", ios::app|ios::out);
            data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
            data.close();
        }
    }
    cout<<"\n\n\t\tRecord inserted successfully!";
}

void Shopping :: edit(){
    fstream data, data1;
    int pkey,c, token = 0;
    float p, d;
    string n;

    cout<<"\n\t\t\t Modify the record";
    cout<<"\n\t\t\t Product code: ";
    cin>>pkey;

    data.open("database.txt", ios::in);
    if(!data){
        cout<<"\n\n File does not exist!";
    }
    else{
        data1.open("database1.txt", ios::app|ios::out);

        data>>pcode>>pname>>price>>dis;

        while(!data.eof()){
            if(pkey == pcode){
                cout<<"\n\t\t\t New code of Product: ";
                cin>>c;
                cout<<"\n\t\t\t New name of product: ";
                cin>>n;
                cout<<"\n\t\t\t New price of product: ";
                cin>>p;
                cout<<"\n\t\t\t New discount on product: ";
                cin>>d;

                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";
                token++;
            }
            else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
            }

            data>>pcode>>pname>>price>>dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0){
            cout<<"\n\n\t\t Record Not Found!";
        }
        else{
            cout<<"\n\t\t Modified Successfully!";
        }
    }
}

void Shopping :: rem(){
    fstream data, data1;
    int pkey, token = 0;
    
    cout<<"\n\t\t\t Delete Product";
    cout<<"\n\t\t\t Product code: ";
    cin>>pkey;

    data.open("database.txt", ios::in);
    if(!data){
        cout<<"\n\n File does not exist!";
    }
    else{
        data1.open("database1.txt", ios::app|ios::out);

        data>>pcode>>pname>>price>>dis;

        while(!data.eof()){
            if(pkey == pcode){
                
                cout<<"\n\n\t\t Product deleted successfully";
                token++;
            }
            else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
            }

            data>>pcode>>pname>>price>>dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token == 0){
            cout<<"\n\n\t\t Record Not Found!";
        }
    }
}

void Shopping :: list(){
    fstream data;

    data.open("database.txt", ios::in);
    cout<<"\n\n_______________________________________________________________________\n";
    cout<<"\tProduct Number\t\tName\t\tPrice\t\tDiscount\n";
    cout<<"\n\n______________________________________________________________________\n";
    data>>pcode>>pname>>price>>dis;

    while(!data.eof()){
        cout<<"\t\t"<<pcode<<"\t\t"<<pname<<"\t\t"<<price<<"\t\t"<<dis<<"\n";
        data>>pcode>>pname>>price>>dis;
 
    }
    data.close();
}

void Shopping :: receipt(){
    fstream data;
    int arrCode[100], arrQuantity[100];
    int c = 0;
    char choice;
    float amount = 0, dis = 0, total = 0;

    cout<<"\n\n\t\t\t\t RECEIPT ";

    data.open("database.txt", ios::in);
    if(!data){
        cout<<"\n\n\t Empty Database";
    }
    else{
        data.close();
        
        list(); //show user what products available and their details

        cout<<"\n______________________________________________\n";
        cout<<"\n                                              \n";
        cout<<"\n           Please place the order             \n";
        cout<<"\n______________________________________________\n"; 
        
        do{
            m:
            cout<<"\n\n Enter product code : ";
            cin>>arrCode[c];
            cout<<"\n\n Enter the product quantity : ";
            cin>>arrQuantity[c];

            for(int i = 0; i<c; i++){

                if( arrCode[c] == arrCode[i]){
                    cout<<"\n\n Duplicate product code. Please try again!";
                    goto m;
                }
            }
            c++;
            cout<<"\n\n Do you wnat to buy another product?\n If yes press y else n : ";
            cin>>choice;

        }while(choice == 'y');

        cout<<"\n\n\t\t____________________________RECEIPT____________________________\n";
        cout<<"\n Product No\t Product Name\t Product Quantity      Price\t    Amount\t    Amount after discount\n";
        
        for(int i = 0; i<c; i++){
            data.open("database.txt", ios::in);
            data>>pcode>>pname>>price>>dis;

            while(!data.eof()){
                
                if(pcode == arrCode[i]){

                    amount = price*arrQuantity[i];
                    dis = amount -(amount * dis/100);
                    total = total + dis;

                    cout<<"\n\t"<<pcode<<"\t\t"<<pname<<"\t\t"<<arrQuantity[i]<<"\t\t"<<price<<"\t\t"<<amount<<"\t\t"<<dis;
                }
                data>>pcode>>pname>>price>>dis;
            }
            data.close();
        }
        
    }
    cout<<"\n\n______________________________________";
    cout<<"\n Total Amount : "<<total<<"\n";
        
}

int main(){

    Shopping s;
    s.menu();
}