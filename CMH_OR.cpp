/*********************************
This is a simulation of CHandy-Misra-Hass deadlock detection for OR Model
Autilr: Sasnak Kuntimaddi
**********************************/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>

using namespace std;

//Function to detect deadlock
void engaging_query(vector<std::vector<int>> &graph, int init, int dest);

//Function to display graph
void display_graph(vector<vector<int>> mat);

//Function to detect Knot
void reply_query(vector<std::vector<int>> &graph, int init, int dest);

//Number of proccesses in the system
int no_proccesses;
vector<bool> wait_msg;
vector<int> msg_count;

//Deadlock count; call to check for knot if only 2 or more than 2 deadlock cycles are present
int no_deadlocks = 0;
int no_knots = 0;

//Deadlock flag - 0 for false, 1 for true
bool deadlock_flag = 0;

// The main - The program execution starts from here
int main() {

	//Proccess ID of the proccess initiating the probe
	int pid_probe;

	//Enter the number of sites and proccesses per site in the system
	int sites = 0;
	cout <<"Enter number of sites(minimum value greater than 1):"<<endl;
	cin >> sites;
	
	for(int i = 0; i< sites; i++)
	{
		int temp;
		cout<<"Enter number of processes for site"<<(i+1)<<": (minimum value greater than 1)"<<endl; 
		cin>>temp;
		no_proccesses += temp;
	}
	cout << "Total number of sites="<<sites<<"; Total number of processes="<<no_proccesses<< endl;

	if (no_proccesses > 1) 
	{
		

		vector<vector<int>> wait_graph(no_proccesses);	
		wait_msg.assign(no_proccesses,false);
		msg_count.assign(no_proccesses,0);
		
		//Enter the wait-graph. (nxn) matrix.
		cout << "Enter the wait graph for processes; Enter 1 if the process is dependent and 0 if not." << endl;
		
		//Input the wait graph values
		for (int from = 0; from < no_proccesses; from++)
		{
			for (int to = 0; to < no_proccesses; to++)
			{
				int temp;
				cout << "Process "<< (from+1) <<" dependent on "<<(to+1)<<"(1/0) :";
				cin >> temp;
				if (temp == 0 || temp == 1) {
					wait_graph.at(from).push_back(temp);				
				}
			}
		}

		cout << endl;
		
		//display wait for graph
		cout << "The wait-for graph is : " << endl;
		display_graph(wait_graph);
		cout << endl;

		//Enter the proccess initiating the probe
		cout << "Enter the proccess initiating the probe (Betwwen 1 and no. of proccesses)" << endl;
		cin >> pid_probe;
		if (pid_probe <0 || pid_probe > no_proccesses ) 
		{
			cout<<"The enterd value is not valid. Exiting"<<endl;
			return(0);
		}
		
		pid_probe = pid_probe - 1;

		//Initializing the probe to detect deadlock
		cout << "Initiating Probe....." << endl << endl;
		cout << "DIRECTION \t PROBE \t MESSAGES \t WAIT FLAG"<< endl;

		//Detecting deadlock
		for (int col = 0; col < no_proccesses; col++)
		{
			if (wait_graph.at(pid_probe).at(col) == 1)
			{
                              cout << " S" << (pid_probe + 1) << " --> S" << (col + 1) << "     (" << (pid_probe + 1) << "," << (pid_probe + 1) << "," << (col + 1) << ")" << " , \t"<< wait_msg[pid_probe]<<" , \t"<<msg_count[pid_probe]<<endl;
				engaging_query(wait_graph, pid_probe, col);
			}
		}
		cout<<"Number of deadlocks detected:"<<no_deadlocks<<endl;
		//Start the reverse process and try to reach the start node now.
		cout<<"Printing wait message array = [";
		for(int m = 0; m<msg_count.size(); m++){ cout<<msg_count.at(m)<<" , ";}
		cout<<"]"<<endl;
		
		
		if(no_deadlocks >= 2 )
		{
			cout<<"\n Detecting knot by checking on the response messages."<<endl;
			vector<vector<int>> wait_graph_copy(wait_graph);
			for (int col = no_proccesses; col > 0; col--)
			{
			        if (wait_graph.at(col-1).at(pid_probe) == 1)
				{
					cout << " S" << (pid_probe + 1) << " --> S" << (col) << "     (" << (pid_probe + 1) << "," << (pid_probe + 1) << "," << (col) << ")" <<" , \t"<< wait_msg[pid_probe]<<" , \t"<<msg_count[pid_probe]<<endl;
					reply_query(wait_graph_copy, pid_probe, (col-1));
				}
			}
		}
		cout<<"Number of knots detected:"<<no_knots<<endl;
	        if(no_deadlocks == no_knots)
	        {
			cout << "Equal number of Deadlock and Knot detectied. \n All sent messages were received. \nHence the Chandy-Misra-Hass OR detected is validated." << endl;
	        }
	}
	else {
		cout << "Deadlock detection not possbile. No proccess running in the system" << endl;
	}

	return 0;
}

void display_graph(vector<vector<int>> wait_graph)
{
	int n = wait_graph.at(0).size();
	int m = wait_graph.size();

	//Top Column
	cout << "\t";
	for (int j = 0; j < m; j++) {
		cout << "S" << (j + 1) << "\t";
	}
	cout << endl;	
	//Side column and values
	for (int i = 0; i<m; i++)
	{
		cout << "S" << (i + 1) << "\t";
		for (int j = 0; j<n; j++)
		{
			cout << wait_graph.at(i).at(j) << "\t";
			if (wait_graph.at(i).at(j) ==1)
			{
				msg_count[i] += 1;
				wait_msg[i] = true;
			}
		}
		cout << "\n";
	}
}

void engaging_query(vector<std::vector<int>> &graph, int init, int dest)
{
	int end = no_proccesses;
	for (int col = 0; col < end; col++)
	{
		if (graph[dest][col] == 1)
		{
			if (init == col)
			{
				cout << " S" << (dest + 1) << " --> S" << (col + 1) <<"     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << " --------> DEADLOCK DETECTED HERE" << endl;
				deadlock_flag = 1;
				no_deadlocks += 1;
				break;
			}
									
			cout << " S" << (dest + 1) << " --> S" << (col + 1) << "     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << " ,\t "<< wait_msg[dest]<<" ,\t "<<msg_count[dest]<<endl;			
			engaging_query(graph, init, col);
		}
	}
}

void reply_query(vector<std::vector<int>> &graph, int init, int dest)
{
	int end = no_proccesses;
	for (int col = (end-1); col >= 0 ; --col)				
	{
	        //cout<<"\tdetectKnot() -- init="<<(init+1)<<" dest="<<(dest+1)<<" .col"<<(col+1)<<endl;
		if (graph[col][dest] == 1)
		{
			//cout<<"**dest:"<<dest<<" ,wait_msg_no:"<<wait_msg[dest]<<" ,msg_count:"<<msg_count[dest]<<endl;
			if (msg_count[dest] != 0) { msg_count[dest] -= 1; }
			if (msg_count[dest] == 0) { wait_msg[dest] = false; }
			if (init == col)
			{
				cout << " S" << (dest + 1) << " --> S" << (col+1) <<"     (" << (init + 1) << "," << (dest + 1) << "," << (col+1) << ")" << " --------> KNOT DETECTED HERE" << endl;
				no_knots += 1;
				if(wait_msg[dest] == false && msg_count[dest] == 0)
				{
					break;
				}
			}
			if (msg_count[dest] == 0 && wait_msg[dest] == false) {
			       graph[col][dest] = 0;
			}
			
			cout << " S" << (dest + 1) << " --> S" << (col + 1) << "     (" << (init + 1) << "," << (dest + 1) << "," << (col+1) << ")" <<" , \t"<< wait_msg[dest]<<" , \t"<<msg_count[dest]<<endl;
			reply_query(graph, init, col);
		}
	}
}
