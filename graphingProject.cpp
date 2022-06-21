// Syed Mohammad Hadi Ul Hassan 2020475
// Abdullah Farooq 2020022
// Muhammad Hamza Azeem 2020296
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <queue>
#include <C:/Users/User/Desktop/DSA_Project/SDL2-2.0.18/i686-w64-mingw32/include/SDL2/SDL.h>
using namespace std;

#define inf 1e9
struct neighbors{
    string name;
    float weight;
    neighbors *next;
};

struct node{
    string n;
    int x, y, degree;
    float keyvalue;
    neighbors *nb;
    node *next;
    node *parent;
    bool inHeap;
};

class comparison{
    public:
    int operator()(node *a, node* b){
        return a->keyvalue>b->keyvalue;
    }
};

class AdjList{
    private:
    node *head;
    double t ,r, inc;
    public:
    AdjList(){
        t = 0.1;
        r = 100;
        inc = 0.075;
        head = NULL;
    }
    
    void insertVertex(string name){
        node *newNode =new node;
        newNode->next = NULL;
        node *temp = head;

        while(temp != NULL){
            if(temp->n == name)
                return;
            temp = temp->next;
        }

        if(head == NULL){
            newNode->n = name;
            newNode->degree = 0;
            newNode->x = (r*cos(t)) + 750;
            newNode->y = (r*sin(t)) + 400;
            newNode->parent = NULL;
            newNode->inHeap = false;
            head = newNode;
            t += inc;
            if(t >= 6.28){
                t = inc;
                r+= 30;
            }
            return;
        }
        temp = head;

        while(temp->next != NULL){
            temp = temp->next;
        }
        newNode->n = name;
        newNode->degree = 0;
        newNode->x = (r*cos(t)) + 750;
        newNode->y = (r*sin(t)) + 400;
        newNode->parent = NULL;
        newNode->inHeap = false;
        temp->next = newNode;
        t += inc;
        if(t >= 6.28){
            t = inc;
            r+= 30;
        }
        return;
    }

    void insertEdge(string n1, string n2, float w){
        neighbors *newNeighbor = new neighbors;
        newNeighbor->name = n2;
        newNeighbor->weight = w;
        newNeighbor->next = NULL;

        node *temp = head;

        while(temp->n!=n1){
            temp = temp->next;
        }
        temp->degree++;
        if(temp->degree == 1){
            temp->nb = newNeighbor;
            return;
        }
        neighbors *temp2 = temp->nb;
        while(temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = newNeighbor;
        return;
    }

    int numOfNodes(){
        int count = 0;
        node *temp = head;
        while(temp != NULL){
            count++;
            temp = temp->next;
        }
        return count;
    }

    void highestDegree(){
        int highestDeg = head->degree;
        string highestName = head->n;
        node *temp = head;

        while(temp->next != NULL){
            if(highestDeg < temp->next->degree){
                highestDeg = temp->next->degree;
                highestName = temp->next->n;
            }
            temp = temp->next;
        }

        cout << "The node with the highest degree is: " << highestName << "\nand its degree is: " << highestDeg << endl;
    }

    void lowestDegree(){
        int lowestDeg = head->degree;
        string lowestName = head->n;
        node *temp = head;

        while(temp->next != NULL){
            if(lowestDeg > temp->next->degree){
                lowestDeg = temp->next->degree;
                lowestName = temp->next->n;
            }
            temp = temp->next;
        }

        cout << "The node with the highest degree is: " << lowestName << "\nand its degree is: " << lowestDeg << endl;
    }

    void displayList(){
        node *temp = head;

        while(temp != NULL){
            cout << temp->n <<": ";
            neighbors *temp2 = temp->nb;
            while(temp2 != NULL){
                cout << "-->" << temp2->name;
                temp2 = temp2->next;
            }
            cout << endl;
            temp = temp->next;
        }
    }
    void searchNode(string key){
        node *temp = head;
        while(temp != NULL){
            if(temp->n == key){
                neighbors *temp2 = temp->nb;
                cout << temp->n <<": ";
                while(temp2 != NULL){
                    cout <<"-->" << temp2->name;
                    temp2 = temp2->next;
                }
                return;
            }
            temp = temp->next;
        }
        cout <<"This node could not be found!\n";
    }

    void degreeOfNode(string key){
        node *temp = head;
        while(temp != NULL){
            if(temp->n == key){
                cout << "The degree of node " << temp->n << " is " << temp->degree << endl;
                return;
            }
            temp = temp->next;
        }
        cout <<"This node could not be found!\n";
    }

    float findX(string name){
        node *temp = head;
        while(temp->n != name){
            temp = temp->next;
        }
        return temp->x;
    }

    float findY(string name){
        node *temp = head;
        while(temp->n != name){
            temp = temp->next;
        }
        return temp->y;
    }

    void displayGraph(){
        // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",20, 20, 1500, 800,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    // Create a rectangle
    SDL_Rect rectangle;
    /*;*/

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    

    SDL_Event event;
        
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        node *temp = head;

        // Do our drawing
        while(temp != NULL)
        {
            rectangle.x = temp->x;
            rectangle.y = temp->y;
            rectangle.w = 5;
            rectangle.h = 5;
            SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &rectangle);
            temp = temp->next;
        }
        temp = head;
        while(temp!=NULL){
            SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
            neighbors *temp2 = temp->nb;
            while(temp2!=NULL){
                SDL_RenderDrawLine(renderer,temp->x,temp->y,findX(temp2->name),findY(temp2->name));
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        

        //SDL_RenderDrawRect(renderer,&rectangle);


        // Finally show what we've drawn
        SDL_RenderPresent(renderer);
        bool end = false;

        while(!end){
            while(SDL_PollEvent(&event)){
                // Handle each specific event
                if(event.type == SDL_QUIT){
                    gameIsRunning= false;
                    end = true;
                }
            }
        }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();
    }

    void createMST(string name){
        node *temp = head;
        while(temp->n!=name){
            temp = temp->next;
        }
        node *temp2 = head;
        while(temp2 != NULL){
            temp2->keyvalue = inf;
            temp2 = temp2->next;
        }

        priority_queue <node*, vector<node*>, comparison> pq;
        temp2 = head;
        while(temp2 != NULL){
            pq.push(temp2);
            temp2->inHeap = true;
            temp2=temp2->next;
        }
        temp->keyvalue = 0;
        node *u;
        temp2 = head;

        while(!pq.empty()){
            u = pq.top();
            pq.pop(); 
            u->inHeap= false;
            neighbors *nb = u->nb;

            while(nb!=NULL){
            node *trav = head;
                while(trav->n != nb->name){
                    trav = trav->next;
                }
                if(trav->inHeap){
                    if(trav->keyvalue > nb->weight){
                        trav->keyvalue = nb->weight;
                    }
                    trav->parent = u;
                }
                nb = nb->next;
            }
        }
        showMST();
    }

    void showMST(){

            // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",20, 20, 1500, 800,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    // Create a rectangle
    SDL_Rect rectangle;
    /*;*/

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    

    SDL_Event event;
        
        
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        node *temp = head;
        while(temp != NULL)
        {
            rectangle.x = temp->x;
            rectangle.y = temp->y;
            rectangle.w = 5;
            rectangle.h = 5;
            SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &rectangle);
            temp = temp->next;
        }
        temp = head;
        while(temp!=NULL){
            SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);
            if(temp->parent != NULL){
                SDL_RenderDrawLine(renderer,temp->x,temp->y,temp->parent->x,temp->parent->y);
            }
            temp = temp->next;
        }
        SDL_RenderPresent(renderer);
        bool end = false;

        while(!end){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    gameIsRunning= false;
                    end = true;
                }
            }
        }

    SDL_DestroyWindow(window);
    
    SDL_Quit();
    }

    void dijkstra(string src, string des){
        node *srcN = head;
        node *desN = head;
        while(srcN->n!=src){
            srcN = srcN->next;
        }
        while(desN->n!=des){
            desN = desN->next;
        }

        node *temp2 = head;
        while(temp2 != NULL){
            temp2->keyvalue = inf;
            temp2 = temp2->next;
        }

        priority_queue <node*, vector<node*>, comparison> pq;
        temp2 = head;
        while(temp2 != NULL){
            pq.push(temp2);
            temp2->parent = NULL;
            temp2->inHeap = true;
            temp2=temp2->next;
        }
        srcN->keyvalue = 0;
        node *u;
        temp2 = head;

        while(!pq.empty()){
            u = pq.top();
            pq.pop();
            u->inHeap= false;
            neighbors *nb = u->nb;

            while(nb!=NULL){
            node *trav = head;
                while(trav->n != nb->name){
                    trav = trav->next;
                }
                if(trav->inHeap){
                    if(trav->keyvalue > nb->weight + u->keyvalue){
                        trav->keyvalue = nb->weight + u->keyvalue;
                    }
                    trav->parent = u;
                }
                nb = nb->next;
            }
        }
        node *temp = head;
        cout << "Distance of all nodes from source node: \n";
        while(temp!=NULL){
            cout << temp->n << ": " << temp->keyvalue << endl;
            temp = temp->next;
        }
        showDijkstra(desN);
    }

    void showDijkstra(node *desN){
        
            // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",20, 20, 1500, 800,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    // Create a rectangle
    SDL_Rect rectangle;
    /*;*/

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    

    SDL_Event event;
        
        
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        node *temp = desN;
        while(temp != NULL)
        {
            rectangle.x = temp->x;
            rectangle.y = temp->y;
            rectangle.w = 5;
            rectangle.h = 5;
            if(temp==desN){
                SDL_SetRenderDrawColor(renderer,255,0,0,SDL_ALPHA_OPAQUE);
            }
            else
                SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &rectangle);
            temp = temp->parent;
        }
        temp = desN;
        while(temp!=NULL){
                SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);;
            
            cout << temp->n << "<--";
            if(temp->parent != NULL){
                SDL_RenderDrawLine(renderer,temp->x,temp->y,temp->parent->x,temp->parent->y);
            }
            temp = temp->parent;
        }
        SDL_RenderPresent(renderer);
        bool end = false;

        while(!end){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    gameIsRunning= false;
                    end = true;
                }
            }
        }

    SDL_DestroyWindow(window);
    
    SDL_Quit();
    }
};


int main(int argc, char* argv[]){

    AdjList L;

    string col1, col2, line1, line2;
    double w;
    ifstream in("PPI-I.txt");
    while (getline(in, line1))
    {
        istringstream extraction(line1);
        extraction >> col1 >> col2 >> w;
        L.insertVertex(col1);
        L.insertVertex(col2);

    }
    
    in.clear();
    ifstream on("PPI-I.txt");
    while (getline(on, line2))
    {
        istringstream extraction(line2);
        extraction >> col1 >> col2 >> w;
        L.insertEdge(col1, col2, w);
        L.insertEdge(col2, col1, w);

    }

    int c;
    char a;
    string key, key2;
    do{
        system("CLS");
        cout << "1.Display Adjacency List\n2.Search for Neighbors of node\n3.Count number of nodes\n";
        cout << "4.Display node of highest degree\n5.Display node of lowest degree\n6.Show degree of a node\n";
        cout << "7.Display graph\n8.Create MST\n9.Calculate shortest path\n0.Exit\n";
        cin >> c;
        switch(c){
            case 1:
                system("CLS");
                L.displayList();
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 2 :
                system("CLS");
                cout <<"Enter the name of the node (e.g. TFC3): ";
                cin >> key;
                L.searchNode(key);
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 3:
                system("CLS");
                cout << "Number of nodes: " << L.numOfNodes() << "\n";
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 4:
                system("CLS");
                L.highestDegree();
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 5:
                system("CLS");
                L.lowestDegree();
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 6:
                system("CLS");
                cout <<"Enter the name of the node (e.g. TFC3): ";
                cin >> key;
                L.degreeOfNode(key);
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 7:
                system("CLS");
                L.displayGraph();
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 8:
                system("CLS");
                cout  <<"Enter the name of the source node for the MST (e.g. TFC3): ";
                cin >> key;
                L.createMST(key);
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 9:
                system("CLS");
                cout  <<"Enter the name of the source node and destination node seperated by a space (e.g. 'TFC3 FUN30' ): ";
                cin >> key >> key2; 
                L.dijkstra(key, key2);
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;
            case 0:
                system("CLS");
                cout << "Thank you!!!";
                break;
            default:
                system("CLS");
                cout << "That is not a valid option!!!";
                cout <<"\nPress any key to continue...";
                cin >> a;
                break;            
        }

    }while(c!=0);
    return 0;
}