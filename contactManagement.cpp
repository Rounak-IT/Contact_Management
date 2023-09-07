#include <iostream>
#include "vector"
#include "list"
#include "iterator"
using namespace std;

                       ////////////////////            Edge Class         /////////////////////
class Edge{
public:
    int destinationContactNumber;

    Edge();
    Edge(int destVID);

    void setDestVID(int destVID);
    int getDestinationContactID() const;
};
                   ///////////////////  Constructors for Edge Class   /////////////////////

/*   Default Constructors with no parameters   */
Edge::Edge() {}

/*   Parametrized Constructors   */
Edge::Edge(int destCNum) {
    destinationContactNumber = destCNum;
}

               ////////////////////  Functions for Edge class   ///////////////////////

void Edge::setDestVID(int destCNum) {
    destinationContactNumber = destCNum;
}

int Edge::getDestinationContactID() const {
    return destinationContactNumber;
}

                         ///////////////////////   Contact Class /////////////////////
                         //////     Represents a contact stored in the graph   //////

class Contact{
public:
    long number;
    string name;
    string new_name;

    list<Edge> edgeList;

    void setName(string name);
    void updateName(string newName);
    void updateContactbyName(string newName);
    string getName();

    void setNumber(long number);
    void updateNumber(long newNo);
    long getNo();

    list<Edge> getEdgeList();
    void printEdgeList();
};
             //////// Functions for the Contact Class /////////

void Contact::updateName(string newName) {
    name = newName;
}

string Contact::getName() {
    return name;
}

void Contact::setName(string name) {
    this->name = name;
}

void Contact::setNumber(long number) {
    this->number = number;
}

void Contact::updateNumber(long newNo) {
    number = newNo;
}
void Contact::updateContactbyName(string newName) {
    name = newName;
}
long Contact::getNo() {
    return number;
}

list<Edge> Contact::getEdgeList() {
    return edgeList;
}

void Contact::printEdgeList() {
    cout<<"[";
    for(auto i = edgeList.begin();i != edgeList.end();i++){
        cout<<i->getDestinationContactID()<<" --> ";
    }
    cout<<"]"<<endl;
}

////////////////   Graph Class  ////////////////

class Graph{
public:
    vector<Contact> contacts;      // Vector is a dynamic array: the one used here stores all contacts in the graph.
    vector<Contact> contacts_in_alphabetical_order;
    int numVertices = contacts.size();

    void addContactByNumber(Contact c1);
    void printGraph();
    void deleteContactNyNumber(long num);
    void deleteContactbyName(string name);
    void addEdgeByNumber(long num1,long num2);
    void updateContact(long num,long new_num);
    void updateContactbyName(string name,string new_name);
    void deleteEdgeByNumber(long fromContact,long toContact);
    void traversal();
    Contact getContactByNumber(long num);
    Contact getContactByName(string name);
private:
    bool checkIfVertexExistsByNumber(long num);
    bool checkIfEdgeExistsByNumber(long num1,long num2);
};

void Graph::addContactByNumber(Contact c1) {
    bool check1 = checkIfVertexExistsByNumber(c1.getNo());

    if(check1){
        cout<<"Another contact with the same number already exists."<<endl;
    }else{
        contacts.push_back(c1);
        cout<<"Contact added successfully."<<endl;
    }
}

bool Graph::checkIfVertexExistsByNumber(long num) {
    for(auto & contact : contacts){
        if(contact.getNo() == num){
            return true;
        }
    }
    return false;
}

void Graph::addEdgeByNumber(long num1, long num2) {
    bool c1 = checkIfVertexExistsByNumber(num1);
    bool c2 = checkIfVertexExistsByNumber(num2);

    if(c1 && c2){
        bool c3 = checkIfEdgeExistsByNumber(num1,num2);
        if(c3){
            cout<<"Edge already exists."<<endl;
        }else{
            for(auto & contact : contacts){
                if(contact.getNo()==num1){
                    Edge e(num2);
                    contact.edgeList.push_back(e);
                }
                else if(contact.getNo()==num2){
                    Edge e(num1);
                    contact.edgeList.push_back(e);
                }
            }
            cout<<"Edge successfully added."<<endl;
        }
    }
}

bool Graph::checkIfEdgeExistsByNumber(long num1, long num2) {
    Contact c = getContactByNumber(num1);
    list<Edge> e = c.getEdgeList();
    list<Edge>::iterator i;
    for(i = e.begin();i!= e.end();i++){
        if(i->getDestinationContactID()==num2){
            return true;
        }
    }
    return false;
}

Contact Graph::getContactByNumber(long num) {
    Contact temp;
    for(auto & contact: contacts){
        temp = contact;
        if(temp.getNo()==num){
            return temp;
        }
    }
}

Contact Graph::getContactByName(string name) {
    Contact temp;
    for(auto & contact: contacts){
        temp = contact;
        if(temp.getName()==name){
            return temp;
        }
    }
}

void Graph::printGraph() {
    for(auto & contact:contacts){
        Contact temp = contact;
        cout<<temp.getName()<<"("<<temp.getNo()<<")  -->  ";
        temp.printEdgeList();
    }
}

void Graph::deleteEdgeByNumber(long fromContact, long toContact) {
    bool check = checkIfEdgeExistsByNumber(fromContact,toContact);
    if(check){
        for(auto & contact : contacts){
            if(contact.getNo()==fromContact){
                list<Edge>::iterator i;
                for(i = contact.edgeList.begin();i!=contact.edgeList.end();i++){
                    if(i->getDestinationContactID()==toContact){
                        contact.edgeList.erase(i);
                        break;
                    }
                }
            }
            else if(contact.getNo()==toContact){
                list<Edge>::iterator i;
                for(i = contact.edgeList.begin();i!=contact.edgeList.end();i++){
                    if(i->getDestinationContactID()==fromContact){
                        contact.edgeList.erase(i);
                        break;
                    }
                }
            }
        }
    }
    else{
        cout<<"Edge between the given numbers does not exist."<<endl;
    }
}

void Graph::deleteContactNyNumber(long num) {
    int contactIndex = 0;
    for(int i=0;i<contacts.size();i++) {
        if (contacts.at(i).getNo() == num) {
            contactIndex = i;
        }
    }
    list<Edge>::iterator i;
    for(i = contacts.at(contactIndex).edgeList.begin(); i != contacts.at(contactIndex).edgeList.end(); i++){
        deleteEdgeByNumber(i->getDestinationContactID(),num);
    }
    contacts.erase(contacts.begin()+contactIndex);

    cout<<"Contact deleted successfully."<<endl;
}

void Graph::deleteContactbyName(string name) {
    int contactIndex = 0;
      for(int i=0;i<contacts.size();i++) {
        if (contacts.at(i).getName() == name) {
            contactIndex = i;
                    }
    }
    int num=contacts.at(contactIndex).getNo();
    list<Edge>::iterator i;
    for(i = contacts.at(contactIndex).edgeList.begin(); i != contacts.at(contactIndex).edgeList.end(); i++){
        deleteEdgeByNumber(i->getDestinationContactID(),num);
    }
    contacts.erase(contacts.begin()+contactIndex);

    cout<<"Contact deleted successfully."<<endl;
}
void Graph::updateContact(long num, long new_number) {
    bool check = checkIfVertexExistsByNumber(num);
    if(check){
        for(auto & contact : contacts){
            if(contact.getNo()==num){
                contact.setNumber(new_number);
                break;
            }
        }
    }
    cout<<"Contact updated successfully."<<endl;
}
void Graph::updateContactbyName(string name, string new_name) {
  
       int contactIndex = 0;
      for(int i=0;i<contacts.size();i++) {
        if (contacts.at(i).getName() == name) {
            contactIndex = i;
                    }
             }  
             int num=contacts.at(contactIndex).getNo();
              bool check = checkIfVertexExistsByNumber(num);
    if(check){
        for(auto & contact : contacts){
            if(contact.getNo()==num){
                contact.setName(new_name);
                break;
            }
        }
    }
    cout<<"Contact updated by name successfully."<<endl;
}
void Graph::traversal() {
    vector<Contact>::iterator i;
    cout<<endl<<endl<<"Contacts List:"<<endl;
    int count = 1;
    for(auto & contact : contacts){
        cout<<count<<".\t"<<contact.getName()<<"\t"<<contact.getNo()<<endl;
        count++;
    }
}

int main(){
    Contact c;
    int choice;
    int option = 1;
    string name;
    string new_name;
    long num,new_num;
    long num1,num2;
    Graph g;

    while(option != 0){
        cout<<"Which operations do you want to perform?(Enter 0 to exit)"<<endl;
        cout<<"1.Add Contact"<<endl;
        cout<<"2.Update Contact"<<endl;
        cout<<"3.Delete Contact"<<endl;
        cout<<"4.Search for Contact"<<endl;
        cout<<"5.Add Edge"<<endl;
        cout<<"6.Print All Contacts"<<endl;
        cout<<"7.Print All Contacts as Adjacency List"<<endl;
        cout<<"8.Search for Contact by name"<<endl;
        cout<<"9.Delete Contact by name:"<<endl;
        cout<<"10.Update Contact by name:"<<endl;
        cin>>option;
        switch (option) {
            case 1:
                  cout<<endl<<"Enter your name:";
                getline(cin, name);
                getline(cin, name);
                cout<<"Enter your number:";
                cin>>num;
                c.setName(name);
                c.setNumber(num);
                g.addContactByNumber(c);
                break;
            case 2:
                cout<<endl<<"Enter the number:";
                cin>>num;
                cout<<"Enter the new number:";
                cin>>new_num;
                g.updateContact(num,new_num);
                break;
            case 3:
                cout<<"Enter the number of the contact to be deleted:";
                cin>>num;
                g.deleteContactNyNumber(num);
                break;
            case 4:
                cout<<"Enter the number of the contact to be searched:";
                cin>>num;
                c = g.getContactByNumber(num);
                cout<<"Name:  "<<c.getName()<<endl;
                cout<<"Contact:   "<<c.getNo();
                break;
            case 5:
                cout<<"Enter the contacts to be connected:"<<endl;
                cin>>num1>>num2;
                g.addEdgeByNumber(num1,num2);
                break;
            case 6:
                g.traversal();
                break;
            case 7:
                cout<<endl<<"Adjacency List representation of the contact list:"<<endl;
                g.printGraph();
                break;
            case 8:    
                  cout<<"Enter the name of the contact to be searched:";
                 getline(cin, name);
                 getline(cin, name);
                c = g.getContactByName(name);
                cout<<"Name:  "<<c.getName()<<endl;
                cout<<"Contact:   "<<c.getNo();
                break;
            case 9:
                cout<<"Enter the name of the contact to be deleted:";
                getline(cin, name);
                getline(cin, name);
                g.deleteContactbyName(name);
                break;
            case 10:
                cout<<endl<<"Enter the name:";
                getline(cin, name);
                getline(cin, name);
                cout<<"Enter the new name:";
                 getline(cin, new_name);
                g.updateContactbyName(name,new_name);
                break;    
            case 0:
                cout<<"Program exited."<<endl;
                cout<<"Window closing..."<<endl;
                exit(0);
            default:
                cout<<"Enter a proper choice!"<<endl;
                break;
        }
        cout<<endl<<"Do you want to continue?(0/1)"<<endl;
        cin>>choice;
    }
    cout<<"Program exited."<<endl;
 return 0;
}