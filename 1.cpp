#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;



class attrNode
{

public:

	vector<attrNode*> vec; 
	int attribute;	
	int pos_sum;
	int neg_sum;
	int height;
	int yes;
	
};

const int NO_OF_ATTRIBUTE=85;
int arr2[NO_OF_ATTRIBUTE+1],arr3[NO_OF_ATTRIBUTE+1];
int maximum[NO_OF_ATTRIBUTE+1]={41,10,5,6,10,9,9,5,9,9,7,9,9,9,9,9,9,9,9,5,9,9,9,9,9,9,9,9,9,9,9,9,7,9,9,9,9,9,9,9,9,9,8,3,6,4,8,7,7,9,5,6,6,6,9,6,3,7,8,3,6,1,6,5,2,5,1,7,4,8,3,3,4,6,2,8,1,1,2,7,1,2,3,2,2,1};
int minimum[NO_OF_ATTRIBUTE+1]={1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
int leaf=0,num_nodes=0,split_arr[NO_OF_ATTRIBUTE];	
int early_stop = 0 , max_height = 0;
int coo=0,leaaa=0;int foo=0;
double optimal_accuracy =0;
int my_node_count = 0;
vector<vector<attrNode*> > myVector(85);
// slpit function to convert string to int 
void split(string lines){

		string arr[NO_OF_ATTRIBUTE+1];
		
   		int j = 0;
   		stringstream ssin(lines);
   		while ( j < NO_OF_ATTRIBUTE+1){
       		ssin >> arr[j];
       		arr2[j] = atoi(arr[j].c_str());      				
       		j++;
   		}

   		//return arr1;
}

int test_func(attrNode *test_node){
	//cout << "[]][]"<<test_node->attribute<<endl;
	
	if (test_node->attribute== -1 || test_node->attribute== -2){
		return (test_node->attribute== -1)?1:0;
	}
	
	else{
		if (minimum[test_node->attribute]==1){
			//cout << "[]"<<arr3[test_node->attribute]<<endl;
			test_func(test_node->vec[arr3[test_node->attribute]-1]);	
		}else{
			test_func(test_node->vec[arr3[test_node->attribute]]);	
		}
		
	}
	
	
}


void count_complexity(attrNode * test_node){
	// perform inorder travsersal
	if (test_node == NULL){
		return ;
	}
	coo++;
	for (int i=0; i<test_node->vec.size();i++){
		count_complexity(test_node->vec[i]);
	}
	
}

void in_order_travserse(attrNode * test_node){
	// perform inorder travsersal
	if (test_node == NULL){
		return ;
	}
	// coo++;
	// if (test_node->attribute== -2 || (test_node->attribute== -1)){
	// 	leaaa++;
	// }
	//cout << test_node->attribute<<"  ";
	myVector[test_node->height].push_back(test_node);
	for (int i=0; i<test_node->vec.size();i++){
		in_order_travserse(test_node->vec[i]);
	}
	
}

void final_prune(attrNode *root_node, attrNode *check_node){
	
	if (root_node == NULL){
		return ;
	}
	if (root_node == check_node){
		//cout <<"GOTTTTTTTTT"<<endl;
		// prune this node
		root_node->attribute = (root_node->neg_sum>=root_node->pos_sum)?-2:-1;
		vector<attrNode*>().swap(root_node->vec);
		return ;
	}

	for (int i=0; i<root_node->vec.size();i++){
		final_prune(root_node->vec[i],check_node);
	}
}

void check_one(attrNode *root_node){
	
	if (root_node == NULL){
		return ;
	}
	if (root_node->yes==1){
		cout <<"1111111111111111111111"<<endl;
	
		return ;
	}

	for (int i=0; i<root_node->vec.size();i++){
		check_one(root_node->vec[i]);
	}
}

void try_me(attrNode *root_node, attrNode *check_node,	vector<attrNode*> vec, int attribute){
	
	if (root_node == NULL){
		return ;
	}
	if (root_node->yes == 1){
		//cout <<"44 adding: "<<"  "<<endl;
		// add this node
		//cout << check_node->yes<<endl;
//		root_node = new attrNode(*check_node);
//		root_node->yes = -100;
		root_node->attribute = attribute;
		root_node->vec = vec;
		root_node->yes = 0;

		return ;
	}

	for (int i=0; i<root_node->vec.size();i++){
		try_me(root_node->vec[i],check_node,vec,attribute);
	}
}

void assign_yes(attrNode *root_node, attrNode *check_node){
	
	if (root_node == NULL){
		return ;
	}
	if (root_node == check_node){
		//cout <<"YESS"<<endl;
		// prune this node
		root_node->yes = 1;
		//vector<attrNode*>().swap(root_node->vec);
		return ;
	}


	for (int i=0; i<root_node->vec.size();i++){
		assign_yes(root_node->vec[i],check_node);
	}
}

void search(attrNode *root_node, attrNode *check_node){
	
	if (root_node == NULL){
		return ;
	}
	if (root_node == check_node){
		// prune this node
		root_node->attribute = (root_node->neg_sum>=root_node->pos_sum)?-2:-1;
		vector<attrNode*>().swap(root_node->vec);
		return ;
	}

	for (int i=0; i<root_node->vec.size();i++){
		search(root_node->vec[i],check_node);
	}
}

attrNode * prune(attrNode *root_node){

	// travserse and check and prune
	my_node_count++;
	if (root_node == NULL){
		return root_node;
	}
	if (root_node->yes==1){
		//cout <<"55"<<endl;
		// prune this node
		root_node->attribute = (root_node->neg_sum>=root_node->pos_sum)?-2:-1;
		//root_node->yes = 1;
		vector<attrNode*>().swap(root_node->vec);
		return root_node;
	}

	for (int i=0; i<root_node->vec.size();i++){
		prune(root_node->vec[i]);
	}
	return root_node;
}

//attrNode* vector_traverse(attrNode *parent_root_node, double original_accuracy,vector<string> test_examples){
//	// for (int c = 0;c<85;c++){
//	// 	myVector[c].clear();
//	// }
//
//	in_order_travserse(parent_root_node);	// 2d vector created
//	cout <<"---"<<endl;
//	attrNode *max_acc_node = NULL; 
//	double max_accuracy = original_accuracy;
//	cout <<"nodes "<<coo<<endl;
//	cout <<"orig "<<original_accuracy<<" aa "<<max_height<<endl; 
//	// for (int i=max_height;i>=0;i--){
//	// 	cout <<"---- "<<myVector[i].size()<<endl;
//	// 	foo=foo+myVector[i].size();
//	// }
//	//cout <<"foo"<<foo<<endl;
//
//
//	//return NULL;
//	for (int i = max_height; i>= 0; i--){
//		int size_nodes = myVector[i].size();
//		cout <<"---- "<<size_nodes<<endl;
//		for (int j=0; j< size_nodes; j++){
//			// created a copy
//			//cout <<"---- "<<i<<"  "<<j<<endl;
//			attrNode *copy_parent_node ;
//			copy_parent_node = new attrNode();
//			copy_parent_node = parent_root_node;
//			
//			attrNode *to_prune_node = myVector[i][j];
//
//			// prune this node
//			// coo=0;
//			// count_complexity(parent_root_node);
//			// cout <<"Before pruning "<< coo<<endl;
//			attrNode *pruned_parent_node = prune(copy_parent_node,to_prune_node);
//			// coo=0;
//			// count_complexity(parent_root_node);
//			// cout <<"After pruning "<< coo<<endl;
//			
//			//check improvement on pruned_parent_node
//			//Accuracy calculator
//
//			int corr=0, fal=0, total=test_examples.size();
//		  	for (int i=0;i<test_examples.size();i++){
//		  		
//		  		string arr[NO_OF_ATTRIBUTE+1];
//				int j = 0;
//				stringstream ssin(test_examples[i]);
//				while ( j < NO_OF_ATTRIBUTE+1){
//					ssin >> arr[j];
//					arr3[j] = atoi(arr[j].c_str());      				
//					j++;
//				}
//		  		
//		  		int output = test_func(pruned_parent_node); 
//		  		if (output==arr3[NO_OF_ATTRIBUTE]){
//		  			corr++;
//				  }else{
//				  	fal++;
//				  }
//			}
//
//			double pruned_acc=(double)corr/(double)total; 
//			if (pruned_acc >= max_accuracy){
//				max_accuracy = pruned_acc;
//				max_acc_node = to_prune_node;	
//			}
//			//cout <<"maxi"<<max_accuracy<<endl;
//			
//		}
//		//cout <<"maxi"<<max_accuracy<<endl;
//		
//	}
//	// maxi improvement
//	if (max_accuracy == original_accuracy){
//		cout <<"max acc 33 "<<max_accuracy<<endl;
//		return NULL;
//	}
//	attrNode* greedy_parent_root = prune(parent_root_node, max_acc_node); 
//	cout <<"max acc "<<max_accuracy<<endl;
//return greedy_parent_root;
//
//}	


// Information gain calculator

int information_gain(int attribute_arr[NO_OF_ATTRIBUTE],vector<string> examples){
	if (examples.size()<3){
		cout <<"size------------  "<<examples.size()<<endl;
	}	
	
	double pos_class=0,neg_class=0,value_count=0;
	double entropy=0;
	
	for(int i=0;i<examples.size()-2;i++){

		string arr[NO_OF_ATTRIBUTE+1];
		int arr1[NO_OF_ATTRIBUTE+1];
   		int j = 0;
   		stringstream ssin(examples[i]);
   		while ( j < NO_OF_ATTRIBUTE+1){
       		ssin >> arr[j];
       		arr1[j] = atoi(arr[j].c_str());      				
       		j++;
   		}

		if (arr1[NO_OF_ATTRIBUTE]==1)
			pos_class++;
		else
			neg_class++;

	}
	//cout<<pos_class<<" pos_class"<<endl;
	//cout<<neg_class<<" pos_class"<<endl;
	
	entropy = (-1)*(pos_class/(neg_class+pos_class))*(log2(pos_class/(neg_class+pos_class))) + (-1)*(neg_class/(neg_class+pos_class))*(log2(neg_class/(neg_class+pos_class)));

	double IG=0,maximum_IG=0,index_IG=0;

	for (int i=0;i<NO_OF_ATTRIBUTE;i++){
	
		if (attribute_arr[i]==1)
		{
			//cout << "i"<<i <<endl;
			continue;		
		}			
		
		int pos_value[maximum[i]-minimum[i]+1],neg_value[maximum[i]-minimum[i]+1];
		fill_n(pos_value,maximum[i]-minimum[i]+1, 0);
		fill_n(neg_value,maximum[i]-minimum[i]+1, 0);
		for (int j=0;j<examples.size()-2;j++){

				//int row[NO_OF_ATTRIBUTE+1];
				split(examples[j]);
				
				
				if (arr2[NO_OF_ATTRIBUTE]==1){

					if (minimum[i]==1){
						//cout <<"####"<<arr2[i]<<"qwe"<<j<<endl;
					pos_value[arr2[i]-1]+=1;

					//cout<<"asdf"<<pos_value[28]<<endl;
					
					}
					else
						pos_value[arr2[i]]+=1;
				}

				else{
					if (minimum[i]==1){
						//cout <<"####"<<arr2[i]<<"qwe"<<j<<endl;
					neg_value[arr2[i]-1]+=1;
					//cout<<"as"<<neg_value[40]<<endl;
					}
					
					else
						neg_value[arr2[i]]+=1;	
				}
		

		}

		double sum=0,entropy_v=0;

		for (int k=0; k < (maximum[i]-minimum[i]+1); k++){
			if (neg_value[k]==0|| pos_value[k]==0){
				entropy_v=0;
			}

			else{
				entropy_v = (-1)*((double)pos_value[k]/((double)neg_value[k]+(double)pos_value[k]))*(log2((double)pos_value[k]/((double)neg_value[k]+(double)pos_value[k]))) + (-1)*((double)neg_value[k]/((double)neg_value[k]+(double)pos_value[k]))*(log2((double)neg_value[k]/((double)neg_value[k]+(double)pos_value[k])));
				
			}	
		//	cout << (((double)maximum[i]-(double)minimum[i]+1))<< "sf"<<" i "<<i<< endl;
			sum = sum + ((entropy_v)*(pos_value[k]+neg_value[k]))/((double)examples.size()-2);
			
		}

		//cout<<sum<<"s"<<endl;
		
		IG = entropy-sum;
		if (IG<1*pow(10,-10)){			
			IG=0.0;
			
		}
		//cout<<" IG "<<IG<<" index "<< i<<"pos_value "<<pos_value[0]<<"neg_value "<<neg_value[0]<<endl;
		//break;
		if (maximum_IG<=IG){
				
				maximum_IG = IG;
				index_IG = i;
		}
		
		
	}

	//cout << "max IG: "<< index_IG<<endl;
	return index_IG;

}

// ID3 implementation
attrNode *id3(vector<string> examples,char taget_attribute, int attribute_arr[NO_OF_ATTRIBUTE], int height){

	attrNode *Root = new attrNode();
	Root->height = height;
	//cout << "H"<< height<<endl;
	if (max_height <= height){
		max_height = height;
	}
	num_nodes++;
	int pos_count=0,neg_count=0;
	//cout<<"examples size"<<examples.size()-2<<endl;

	for (int i=0; i<examples.size()-2;i++){
		string arr[NO_OF_ATTRIBUTE+1];
		int arr1[NO_OF_ATTRIBUTE+1];
   		int j = 0;
   		stringstream ssin(examples[i]);
   		while ( j < NO_OF_ATTRIBUTE+1){

       		ssin >> arr[j];
       		arr1[j] = atoi(arr[j].c_str());      				
       		j++;
   		}

   		if (arr1[NO_OF_ATTRIBUTE]==1){
       			pos_count++;
       		}

       		if (arr1[NO_OF_ATTRIBUTE]==0){
       			neg_count++;
       	}
	}
	// if (Root->height>0){
	// 	Root->attribute=((neg_count>=pos_count)?-2:-1);
	// 	leaf++;
	// 	return Root;

	// }
	Root->pos_sum = pos_count;
	Root->neg_sum = neg_count;

	if (early_stop == 1){

	if (pos_count+neg_count < 9){
			Root->attribute=((neg_count>=pos_count)?-2:-1);
			leaf++;
			Root->pos_sum = pos_count;
			Root->neg_sum = neg_count;
			return Root;			
		}	
	}
		
	//----cout <<"13 "<<"pos_count "<<pos_count<<" neg count "<<neg_count<<endl;
	if (pos_count==(examples.size()-2)||neg_count==(examples.size()-2)){

		if (pos_count==(examples.size()-2)){	
			Root->attribute=-1;
			leaf++;
			Root->pos_sum = pos_count;
			Root->neg_sum = neg_count;
			return Root;
		}
		if(neg_count==(examples.size()-2)){
	//		cout<<"12"<<endl;
			Root->attribute=-2;
			leaf++;
			Root->pos_sum = pos_count;
			Root->neg_sum = neg_count;
			return Root;
			
		} 

		//cout<<"13"<<endl;
	}
	else{
		int majority_pos=0,majority_neg=0;
		
		for (int i=0;i<examples.size()-2;i++){
			//cout<<"5"<<endl;
			split(examples[i]);
			if (arr2[NO_OF_ATTRIBUTE]==1){
				majority_pos++;
			}
		
			else{
				majority_neg++;
			}
		}


		int count = 0; 
		for (int c=0;c<NO_OF_ATTRIBUTE;c++){
			if (attribute_arr[c]==1){
				count++;
			}
		}

		if (Root->height == NO_OF_ATTRIBUTE -1){
			Root->attribute = (majority_neg>=majority_pos)?-2:-1;
			leaf++;
			Root->pos_sum = majority_pos;
			Root->neg_sum = majority_neg;
			return Root;
		}
		if (count==NO_OF_ATTRIBUTE){
			Root->attribute = (majority_neg>=majority_pos)?-2:-1;
			leaf++;
			Root->pos_sum = majority_pos;
			Root->neg_sum = majority_neg;
			return Root;
		}
		int IG = information_gain(attribute_arr,examples);
		split_arr[IG]++;
		
		//attribute_arr[IG]=1;
		
		Root->attribute = IG;
	

		int no_of_values = maximum[Root->attribute]-minimum[Root->attribute]+1;
		//----cout << "[][]"<<no_of_values<<endl;
		for (int i=0;i<no_of_values;i++){
			int new_att_arr [NO_OF_ATTRIBUTE];
			
			for (int c = 0; c < NO_OF_ATTRIBUTE; c++){
				if (c!=IG){
					new_att_arr[c] = attribute_arr[c];
				}else{
					new_att_arr[c]=1;
				}
			}
			vector<string> examples_v;
			//attrNode *node_v = new attrNode();
			//Root->vec.push_back(node_v);

			for (int j=0;j<examples.size()-2;j++){
					//cout<<"3"<<endl;
					split(examples[j]);
					if (minimum[Root->attribute]==0){
	//					cout<<"3"<<endl;
						if(arr2[Root->attribute] == i){
							examples_v.push_back(examples[j]);
						}	
					}
					else{

						if(arr2[Root->attribute] == i+1){
	//						cout<<"else"<<endl;
							examples_v.push_back(examples[j]);
						}
					}
					  
					
			}

			examples_v.push_back(examples[examples.size()-2]);
			examples_v.push_back(examples[examples.size()-1]);

			
			//----cout<<"examples_v "<<examples_v.size()-2<<endl;
			if (examples_v.size()-2==0){
		
				attrNode *node_v = new attrNode();
				node_v->attribute = (majority_neg>=majority_pos)?-2:-1;
				leaf++;
				num_nodes++;
				node_v->pos_sum = majority_pos;
				node_v->neg_sum = majority_neg;
				node_v->height = height + 1;
				Root->vec.push_back(node_v);
				vector<string>().swap(examples_v);		
			}

	//	cout<<"6"<<endl;
		else{
			//cout <<"H"<<height<<endl;	
			Root->vec.push_back(id3(examples_v,-1,new_att_arr,height+1));
			vector<string>().swap(examples_v);
		}
		
		}
	
	}
	return Root;
		
}

void experiment1(char *argv[]){
	cout <<endl;
	cout << "Experiment 1"<<endl;
	cout <<endl;
	cout << "Effect of early stopping on prediction accuracy"<<endl;
	
	early_stop = 0;
	
	string line;
	int i=0;
	string no_of_rows;
	int n_rows=0;
	vector<string> data_vec;
	vector<string> examples;
	vector<string> test_examples;
	
	ifstream myfile (argv[1]);
  	
	if (myfile.is_open())
  	{	
  		if (getline(myfile,line)){
  			no_of_rows = line;	
		  }
  		n_rows = atoi(no_of_rows.c_str());
		if (getline(myfile,line)){
			string ns = line;	
		}
			  
    	while ( getline (myfile,line))
    	{
      		data_vec.push_back(line);
    	}

    	myfile.close();
  	}
  	
  	// shuffle
	for (int k = 0; k < data_vec.size(); k++) {
	    int r = k + rand() % (data_vec.size() - k); // careful here!
	//    cout <<r<<"  ";
	    swap(data_vec[k], data_vec[r]);
	}
	
	
  	for (int i=0;i<1000;i++){
 		examples.push_back(data_vec[i]);
	 }
	
	for (int i=1000;i<data_vec.size();i++){
		test_examples.push_back(data_vec[i]);
	}

	vector<string>().swap(data_vec);
	ostringstream oss,oss1;

 	 for (int temp = 0; temp < NO_OF_ATTRIBUTE+1; temp++){
    	oss << maximum[temp]; 
    	if (temp<NO_OF_ATTRIBUTE){
    		oss << "\t";	
		}
		
    	
    	oss1 << minimum[temp]; 
    	if (temp<NO_OF_ATTRIBUTE){
    		oss1 << "\t";	
		}
    }

	examples.push_back(oss.str());
	examples.push_back(oss1.str());

  	int attribute_arr[NO_OF_ATTRIBUTE];
  	
  	fill_n(arr2,NO_OF_ATTRIBUTE+1, 0);
  	fill_n(attribute_arr,NO_OF_ATTRIBUTE, 0);
  	
  	// ID3 call
	attrNode *parent_root = id3(examples,-1,attribute_arr,0);

// Accuracy calculator
	
	int corr=0, fal=0, total=examples.size()-2;
  	for (int i=0;i<examples.size()-2;i++){
  		
  		string arr[NO_OF_ATTRIBUTE+1];
		int j = 0;
		stringstream ssin(examples[i]);
		while ( j < NO_OF_ATTRIBUTE+1){
			ssin >> arr[j];
			arr3[j] = atoi(arr[j].c_str());      				
			j++;
		}
  		
  		int output = test_func(parent_root); 
  		if (output==arr3[NO_OF_ATTRIBUTE]){
  			corr++;
		  }else{
		  	fal++;
		  }
	}
  	 

	//cout <<"Number of times an attribute is used as the splitting function"<<endl;
	int new_split[NO_OF_ATTRIBUTE];
	for (int i=0;i<NO_OF_ATTRIBUTE;i++){
		new_split[i]=split_arr[i];	
	}

 
	double acc1=(double)corr/(double)total;
	cout << "Training Dataset prediction accuracy without early stopping -> "<<acc1*100<<" "<<'%'<<endl;
	int leaf1=leaf;
	leaf=0;

	early_stop = 1;
	// ID3 call
	parent_root = id3(examples,-1,attribute_arr,0);
	// Accuracy calculator
	
	corr=0, fal=0, total=examples.size()-2;

  	for (int i=0;i<examples.size()-2;i++){
  		
  		string arr[NO_OF_ATTRIBUTE+1];
		int j = 0;
		stringstream ssin(examples[i]);
		while ( j < NO_OF_ATTRIBUTE+1){
			ssin >> arr[j];
			arr3[j] = atoi(arr[j].c_str());      				
			j++;
		}
  		
  		int output = test_func(parent_root); 
  		if (output==arr3[NO_OF_ATTRIBUTE]){
  			corr++;
		  }else{
		  	fal++;
		  }
	}
	
	double acc2=(double)corr/(double)total;
	cout << "Training Dataset prediction accuracy with early stopping -> "<<acc2*100<<" "<<'%'<<endl;
	int leaf2=leaf;
	leaf = 0 ;



////////////test

	early_stop=0;	
	parent_root = id3(examples,-1,attribute_arr,0);
// Accuracy calculator
	
	corr=0, fal=0, total=test_examples.size();
  	for (int i=0;i<test_examples.size();i++){
  		
  		string arr[NO_OF_ATTRIBUTE+1];
		int j = 0;
		stringstream ssin(test_examples[i]);
		while ( j < NO_OF_ATTRIBUTE+1){
			ssin >> arr[j];
			arr3[j] = atoi(arr[j].c_str());      				
			j++;
		}
  		
  		int output = test_func(parent_root); 
  		if (output==arr3[NO_OF_ATTRIBUTE]){
  			corr++;
		  }else{
		  	fal++;
		  }
	}
  	  
	double acc3=(double)corr/(double)total;
	int leaf3=leaf;
	cout << "Test Dataset prediction accuracy without early stopping -> "<<acc3*100<<" "<<'%'<<endl;
	leaf=0;

	early_stop = 1;
	// ID3 call
	parent_root = id3(examples,-1,attribute_arr,0);
	// Accuracy calculator
	
	corr=0, fal=0, total=test_examples.size();

  	for (int i=0;i<test_examples.size();i++){
  		
  		string arr[NO_OF_ATTRIBUTE+1];
		int j = 0;
		stringstream ssin(test_examples[i]);
		while ( j < NO_OF_ATTRIBUTE+1){
			ssin >> arr[j];
			arr3[j] = atoi(arr[j].c_str());      				
			j++;
		}
  		
  		int output = test_func(parent_root); 
  		if (output==arr3[NO_OF_ATTRIBUTE]){
  			corr++;
		  }else{
		  	fal++;
		  }
	}


	double acc4=(double)corr/(double)total;
	int leaf4=leaf;
	cout << "Test Dataset prediction accuracy with early stopping -> "<<acc4*100<<" "<<'%'<<endl;
	cout <<endl;
	cout << "Effect of early stopping on the number of terminal nodes"<<endl;

	cout << "Number of terminal nodes without early stopping -> "<<leaf1<<endl;
	cout << "Number of terminal nodes with early stopping -> "<<leaf2<<endl;
		cout << endl;
	cout <<"Number of times an attribute is used as the splitting function"<<endl;
	//int new_split[NO_OF_ATTRIBUTE];
	for (int i=0;i<NO_OF_ATTRIBUTE;i++){
		cout<<i+1<<" "<<new_split[i]<<endl;	
	}




}

void experiment2(char *argv[]){

	string line;
	int i=0;
	string no_of_rows;
	int n_rows=0;
	vector<string> data_vec;
	
	vector<string> test_examples;
	 
	ifstream myfile (argv[1]);
  	
	if (myfile.is_open())
  	{	
  		if (getline(myfile,line)){
  			no_of_rows = line;	
		  }
  		n_rows = atoi(no_of_rows.c_str());
		if (getline(myfile,line)){
			string ns = line;	
		}
			  
    	while ( getline (myfile,line))
    	{
      		data_vec.push_back(line);
    	}

    	myfile.close();
  	}	
  	
  	// shuffle
	for (int k = 0; k < data_vec.size(); k++) {
	    int r = k + rand() % (data_vec.size() - k); // careful here!
	//    cout <<r<<"  ";
	    swap(data_vec[k], data_vec[r]);
	}

	
	for (int i=1000;i<data_vec.size();i++){
		test_examples.push_back(data_vec[i]);
	}
	
	int noise_arr[5]={0,5,10,50,100};
	cout<<endl;
	// 0.5% error
	cout<<"Experiment 2"<<endl;
	cout <<endl;
	cout <<"Effect of noise on the prediction accuracy of learned decision tree and complexity of learned decision tree using number of nodes"<<endl;
	cout <<endl;
	for (int i=0;i<5;i++){
		vector<string> examples;
		for (int kk=0;kk<1000;kk++){	
 			examples.push_back(data_vec[kk]);
		}
		num_nodes = 0;	
		cout<<"Percentage of Noise = "<<(double)noise_arr[i]/(double)10<<'%';
		for (int j=0;j<noise_arr[i];j++){
			int r = j + rand() % (examples.size() - j);
			//cout<<"---"<<examples[r]<<endl;
			char last_char= examples[r].at(examples[r].size()-1);
			examples[r].erase(examples[r].size()-1,1);
			int last_col=(int)last_char-48;
			
			if (last_col==0)
				examples[r]+='1';
			else{
				examples[r]+='0';
			}
			
		}
		
		
		ostringstream oss,oss1;

 	 	for (int temp = 0; temp < NO_OF_ATTRIBUTE+1; temp++){
	    	oss << maximum[temp]; 
	    	if (temp<NO_OF_ATTRIBUTE){
	    		oss << "\t";	
			}
			
	    	
	    	oss1 << minimum[temp]; 
	    	if (temp<NO_OF_ATTRIBUTE){
	    		oss1 << "\t";	
			}
    	}

		examples.push_back(oss.str());
		examples.push_back(oss1.str());

	  	int attribute_arr[NO_OF_ATTRIBUTE];
	  	
	  	fill_n(arr2,NO_OF_ATTRIBUTE+1, 0);
	  	fill_n(attribute_arr,NO_OF_ATTRIBUTE, 0);

		attrNode *parent_root = id3(examples,-1,attribute_arr,0);
		int corr=0, fal=0, total=test_examples.size();
  		for (int i=0;i<test_examples.size();i++){
	  		
	  		string arr[NO_OF_ATTRIBUTE+1];
			int j = 0;
			stringstream ssin(test_examples[i]);
			while ( j < NO_OF_ATTRIBUTE+1){
				ssin >> arr[j];
				arr3[j] = atoi(arr[j].c_str());      				
				j++;
			}
	  		
	  		int output = test_func(parent_root); 
	  		if (output==arr3[NO_OF_ATTRIBUTE]){
	  			corr++;
			  }else{
			  	fal++;
			  }
		}
  		  
		cout<<" & accuracy = "<<100*(double)corr/(double)total<<" "<<'%';
		cout <<" & Number of nodes = "<<num_nodes<<endl;
		cout <<endl;
		vector<string>().swap(examples);	
	}
	vector<string>().swap(data_vec);



}
void experiment3(char *argv[]){
	cout <<endl;
	cout <<"Experiment 3" <<endl;
	cout <<endl;
	
	cout <<"Effect of post pruning on the prediction accuracy of test set as a function of number of nodes in tree"<<endl;
	cout <<endl;
	
	string line;
	int i=0;
	string no_of_rows;
	int n_rows=0;
	vector<string> data_vec;
	vector<string> examples;
	vector<string> test_examples;
	 
	ifstream myfile (argv[1]);
  	
	if (myfile.is_open())
  	{	
  		if (getline(myfile,line)){
  			no_of_rows = line;	
		}

  		n_rows = atoi(no_of_rows.c_str());
		
		if (getline(myfile,line)){
			string ns = line;	
		}
			  
    	while ( getline (myfile,line))
    	{
      		data_vec.push_back(line);
    	}

    	myfile.close();

  	}	
  	
  	// shuffle
	for (int k = 0; k < data_vec.size(); k++) {
	    int r = k + rand() % (data_vec.size() - k);
	//    cout <<r<<"  ";
	    swap(data_vec[k], data_vec[r]);
	}
	
	
	for (int kk=0;kk<1000;kk++){	
 	
 			examples.push_back(data_vec[kk]);
	}
	
	for (int i=1000;i<data_vec.size();i++){
		test_examples.push_back(data_vec[i]);
	}
					
	vector<string>().swap(data_vec);
	ostringstream oss,oss1;

 	 for (int temp = 0; temp < NO_OF_ATTRIBUTE+1; temp++){
    	oss << maximum[temp]; 
    	if (temp<NO_OF_ATTRIBUTE){
    		oss << "\t";	
		}
		
    	
    	oss1 << minimum[temp]; 
    	if (temp<NO_OF_ATTRIBUTE){
    		oss1 << "\t";	
		}
    }

	examples.push_back(oss.str());
	examples.push_back(oss1.str());

  	int attribute_arr[NO_OF_ATTRIBUTE];
  	
  	fill_n(arr2,NO_OF_ATTRIBUTE+1, 0);
  	fill_n(attribute_arr,NO_OF_ATTRIBUTE, 0);
  	
  	// ID3 call
	attrNode *parent_root = id3(examples,-1,attribute_arr,0);
	//cout << "max"<<max_height<<endl;
	
	// 	// Accuracy calculator
		
		int corr=0, fal=0, total=test_examples.size();
	  	for (int i=0;i<test_examples.size();i++){
	  		
	  		string arr[NO_OF_ATTRIBUTE+1];
			int j = 0;
			stringstream ssin(test_examples[i]);
			while ( j < NO_OF_ATTRIBUTE+1){
				ssin >> arr[j];
				arr3[j] = atoi(arr[j].c_str());      				
				j++;
			}
	  		
	  		int output = test_func(parent_root); 
	  		if (output==arr3[NO_OF_ATTRIBUTE]){
	  			corr++;
			  }else{
			  	fal++;
			  }
		}	
		double original_accuracy=(double)corr/(double)total; 
		//cout<<original_accuracy<<endl;
		
		coo=0;
		count_complexity(parent_root);
		//cout <<"original compl : "<<coo<<endl;
		int original_complexity = coo;
	
//	in_order_travserse(parent_root);
//	//attrNode *copied_par_node = new attrNode (*parent_root);
//	attrNode *copy_parent_node = new attrNode(*parent_root);
//	//copy_parent_node = new attrNode();
//	//copy_parent_node = parent_root;
//	
//	coo=0;
//	count_complexity(parent_root);
//	cout <<"parent compl before prun : "<<coo<<endl;
//	attrNode *to_prune_node = new attrNode(*myVector[0][0]);
//	attrNode *tp_node = myVector[0][0];
//	
//	assign_yes(parent_root, tp_node);
//	cout <<"p  *** "<<  myVector[0][0]->yes<<endl;
//	attrNode *ll = prune(parent_root);
//	
//	coo=0;
//	count_complexity(parent_root);
//	cout <<"parent compl after prun : "<<coo<<endl;
//	
//	cout << "p  "<<tp_node->yes<<endl;
//	
//	
//	myVector[10][0] = to_prune_node;
//	if (to_prune_node==myVector[0][0]){
//		cout <<"---RAMAN----  "<<endl;
//	}
//	cout << " q "<<myVector[0][0]->yes<<endl;
//	try_me(parent_root,to_prune_node,to_prune_node->vec,to_prune_node->attribute);
//	 
//	cout << " q *** "<<to_prune_node->yes<<endl;
//	
//	coo=0;
//	count_complexity(parent_root);
//	cout <<"parent compl after adding : "<<coo<<endl;
//	
//
//	//Accuracy calculator
//		
//	corr=0, fal=0, total=test_examples.size();
//  	for (int i=0;i<test_examples.size();i++){
//  		
//  		string arr[NO_OF_ATTRIBUTE+1];
//		int j = 0;
//		stringstream ssin(test_examples[i]);
//		while ( j < NO_OF_ATTRIBUTE+1){
//			ssin >> arr[j];
//			arr3[j] = atoi(arr[j].c_str());      				
//			j++;
//		}
//  		
//  		int output = test_func(copy_parent_node); 
//  		if (output==arr3[NO_OF_ATTRIBUTE]){
//  			corr++;
//		  }else{
//		  	fal++;
//		  }
//	}	
//	original_accuracy=(double)corr/(double)total; 
//	cout<<original_accuracy<<endl;
//	
//	check_one(parent_root);
//	
	

//------------------------------------------------------------------------


//

	
	cout << "Prediction accuracy on test set without post pruning : "<<original_accuracy*100<<" "<<'%'<<endl;
	cout << "Number of nodes in tree without post pruning : "<<original_complexity<<endl;
	cout <<endl;
	int iter_number = 0 ;
	while (true){
		for (int p=0;p<85;p++){
			myVector[p].clear();
		}	
		in_order_travserse(parent_root);	// 2d vector created
		attrNode *max_acc_node; 
		double max_accuracy = original_accuracy;
		int max_compl;
		
		for (int i = max_height; i>= 0; i--){
			int size_nodes = myVector[i].size();
			//cout <<"---- "<<size_nodes<<endl;
			for (int j=0; j< size_nodes; j++){
				
				attrNode *to_prune_node = new attrNode(*myVector[i][j]);
				attrNode *tp_node = myVector[i][j];
				
				assign_yes(parent_root, tp_node);
				
				// pruning
				my_node_count = 0;
				prune(parent_root);
				
					//Accuracy calculator
	
				int corr=0, fal=0, total=test_examples.size();
			  	for (int kk=0;kk<test_examples.size();kk++){
			  		
			  		string arr[NO_OF_ATTRIBUTE+1];
					int j = 0;
					stringstream ssin(test_examples[kk]);
					while ( j < NO_OF_ATTRIBUTE+1){
						ssin >> arr[j];
						arr3[j] = atoi(arr[j].c_str());      				
						j++;
					}
			  		
			  		int output = test_func(parent_root); 
			  		if (output==arr3[NO_OF_ATTRIBUTE]){
			  			corr++;
					  }else{
					  	fal++;
					  }
				}
		 
				double pruned_acc=(double)corr/(double)total; 
				if (pruned_acc >= max_accuracy){
					max_accuracy = pruned_acc;
					max_acc_node = myVector[i][j];	
//					coo=0;
//					count_complexity(parent_root);
					max_compl = my_node_count;	
					//cout <<	my_node_count << " -- "<< coo<<endl; 			
				}
				myVector[i][j] = to_prune_node;
				
				try_me(parent_root,to_prune_node,to_prune_node->vec,to_prune_node->attribute);
				
				check_one(parent_root);
			
			}
			
		}
		
			// break points
		if (max_accuracy == original_accuracy && max_compl >= original_complexity ){
			//cout <<"max acc 33 "<<max_accuracy<<endl;
			break;
		}
		if (max_accuracy < original_accuracy){
			//cout <<"less than "<<max_accuracy<<endl;
			break;
		}
		
	// final pruning most greedy node
		final_prune(parent_root,max_acc_node);
		//Accuracy calculator
	
		corr=0, fal=0, total=test_examples.size();
	  	for (int i=0;i<test_examples.size();i++){
	  		
	  		string arr[NO_OF_ATTRIBUTE+1];
			int j = 0;
			stringstream ssin(test_examples[i]);
			while ( j < NO_OF_ATTRIBUTE+1){
				ssin >> arr[j];
				arr3[j] = atoi(arr[j].c_str());      				
				j++;
			}
	  		
	  		int output = test_func(parent_root); 
	  		if (output==arr3[NO_OF_ATTRIBUTE]){
	  			corr++;
			  }else{
			  	fal++;
			  }
		}
	
		
		original_accuracy = max_accuracy;
	//	cout <<"parent accuracy after done "<<original_accuracy<<endl; 		
		coo=0;
		count_complexity(parent_root);
	//	cout <<"parent compl after all done : "<<coo<<endl;		
		original_complexity = coo;		
		check_one(parent_root);	
		
		cout << "Prediction accuracy on test set with post pruning after iteration number : "<<iter_number+1<<" -> "<<original_accuracy*100<<" "<<'%'<<endl;
		cout << "Number of nodes in tree with post pruning after iteration number : "<<iter_number+1<<" -> "<<original_complexity<<endl;
		cout <<endl;
		iter_number++;	
	}
	
	coo=0;
	count_complexity(parent_root);
	int optimal_compl = coo;
	cout << "Optimal tree size after post pruning -> " <<optimal_compl<<endl; 
	
	//Accuracy calculator
	
		corr=0, fal=0, total=test_examples.size();
	  	for (int i=0;i<test_examples.size();i++){
	  		
	  		string arr[NO_OF_ATTRIBUTE+1];
			int j = 0;
			stringstream ssin(test_examples[i]);
			while ( j < NO_OF_ATTRIBUTE+1){
				ssin >> arr[j];
				arr3[j] = atoi(arr[j].c_str());      				
				j++;
			}
	  		
	  		int output = test_func(parent_root); 
	  		if (output==arr3[NO_OF_ATTRIBUTE]){
	  			corr++;
			  }else{
			  	fal++;
			  }
		}
	double optimal_acc = (double)corr/(double)total;
	cout << "Optimal tree prediction accuracy on test set after post pruning -> "<<optimal_acc*100<<" "<<'%'<<endl;
	cout <<endl;
	//-------------------------------------------------
	
}

void experiment4(){


	
}

int main(int argc, char*argv[]){

 //Training file read
	if (strtol(argv[2],NULL,10)==1){
		experiment1(argv);	
		
	}

	if (strtol(argv[2],NULL,10)==2){
		experiment2(argv);	
		
	}

	if (strtol(argv[2],NULL,10)==3){
		experiment3(argv);	
		
	}


}
