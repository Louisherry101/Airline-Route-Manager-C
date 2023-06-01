/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Louis Herry
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <ctype.h>

// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 80

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->word);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);

    apply(l, print_node, "%s\n");
}





void do_the_job1(char *Fname, char *q_num,char *nele2){
    /*
    this program will do question 1 in the assignment.
    the program will take in the file name , question number , and how many data does it wanna show on the csv file
    
    */
    
    char *line = NULL;
    
     
    node_t *ans_out = NULL;
    node_t *get_the_correct_order = NULL;
    ///////////////////////////////
  

    line = Fname;
    line = (char *)malloc(sizeof(char) * MAX_WORD_LEN );
    if (line == NULL) {
    fprintf(stderr, "Argh. Something bad happened with malloc. :-(\n");
    }
    node_t *temp = NULL;

    //setting up some variable for use 

    char file_line [1024];
    FILE *data = fopen(Fname, "r");
    int skip_first = 1;
    int counting = 0;
    int marking = 0;
    int debug = 0;
    if(data == NULL){
        perror("error");
        exit(1);
    }
    //read in the line in the yaml files
    while(fgets(file_line, sizeof(file_line),data)){
        
        
        char *token = strtok(file_line,"\n");
        
        if (skip_first==0){    
        
            if(counting != 13){
                
                char *token2 = strtok(token,":");
                token2 = strtok(NULL,":");
                
                if (temp==NULL){
                    temp = new_node(token2,1);
                }else{
                    temp = add_end(temp,new_node(token2,0));
                }
                
                    
                if (counting == 10 && (strcmp(token2," Canada")==0)){
                    marking = 1;
                }
             
                
                counting++;
            
            }
            else {
                if (marking == 1) {
            
        
                if (ans_out == NULL) {
                // If ans_out is empty, get the first two nodes of temp and add them to ans_out
                node_t *transfer1 = peek_front(temp);
                  temp = remove_front(temp);
                node_t *transfer2 = peek_front(temp);
                temp = remove_front(temp);
            
                ans_out = transfer1;
                ans_out = add_end(ans_out, transfer2);
                } else {
                // Otherwise, add the first two nodes of temp to the end of ans_out
                node_t *transfer1 = peek_front(temp);
                temp = remove_front(temp);
                node_t *transfer2 = peek_front(temp);
                temp = remove_front(temp);
                
                ans_out = add_end(ans_out, transfer1);
                ans_out = add_end(ans_out, transfer2);
                }
            }
                temp = NULL;
                marking = 0;

                char *token2 = strtok(token,":");
                token2 = strtok(NULL,":");
                temp = add_end(temp,new_node(token2,0));
                    
                counting = 1;
                
        
            }
       
        }
        skip_first = 0;
        
    
    }

    //remove all space before outputting the data
    while(ans_out!=NULL){
        node_t *transfer3 = peek_front(ans_out); 
        ans_out = remove_front(ans_out);

        char *a_name = transfer3->word + 1;
        while (!isalpha(a_name[0])){
            a_name = transfer3->word + 1;
        }

        node_t *transfer4 = peek_front(ans_out);
        ans_out = remove_front(ans_out);
        char *shor_form = transfer4->word +1;
    // make the string to output be the exact same thing comparing to the tester    
        char *correct_name = strcat(a_name," (");
        correct_name = strcat(correct_name,shor_form);
        correct_name = strcat(correct_name,")");
        node_t *transfer5 = new_node(correct_name,0);
        get_the_correct_order = add_inorder(get_the_correct_order,transfer5);
    
        debug++;
    }    

    
     char* now_airname = " ";
     node_t *final_output_list = NULL;
     node_t *transfer6 = peek_front(get_the_correct_order);
     int fin_dup = 15;

    //add all the string in order after and sort them 
        while (get_the_correct_order != NULL){
             
             if(strcmp(now_airname,transfer6->word)==0){
                 fin_dup = fin_dup+1;
                 transfer6->duplicate = fin_dup;
                 now_airname = transfer6->word;
                 
             }
             else{
                 final_output_list = add_inorder2(final_output_list, new_node(now_airname,fin_dup));
                 now_airname =  transfer6->word;
                 fin_dup = 1;
        
             }
           

             
            
            get_the_correct_order = remove_front(get_the_correct_order);
            transfer6 = peek_front(get_the_correct_order);
              
        }
            final_output_list = add_inorder2(final_output_list, new_node(now_airname,fin_dup));


        int hard_count = 0;
// output them into a csv file
        FILE *output1;
        int j=0;
        int howmuch = atoi(nele2);
        
        output1 = fopen("output.csv","w");
        fprintf(output1,"subject,statistic\n");
       
         while( final_output_list!=NULL && j<=howmuch){
            node_t *check = peek_front(final_output_list);
            if(hard_count!=2){
                fprintf(output1,"%s,%d",check->word,check->duplicate);
                fprintf(output1,"\n");
            }
            final_output_list = remove_front(final_output_list);
            hard_count++;
            j++;
    
        }
        fclose(output1);

        }





void do_the_job2(char *Fname, char *q_num,char *nele2){
    /*
    this program will solve the problem for question 2. 
    the program will take the file name, question 2 number and how many data does it wanna show in the csv file
    
    
    */
    char *line = NULL;
    
     
    node_t *ans_out = NULL;
    
    ///////////////////////////////
  

    line = Fname;
    line = (char *)malloc(sizeof(char) * MAX_WORD_LEN );
    if (line == NULL) {
    fprintf(stderr, "Argh. Something bad happened with malloc. :-(\n");
    }
    node_t *temp = NULL;

    
    char file_line [1024];
    FILE *data = fopen(Fname, "r");
    int skip_first = 1;
    int counting = 0;
    
    
    if(data == NULL){
        perror("error");
        exit(1);
    }
    //this part will read in the files in the yaml files
    while(fgets(file_line, sizeof(file_line),data)){
        
        
        char *token = strtok(file_line,"\n");
        
        if (skip_first==0){    
            counting++;
            if(counting != 14){
                
                char *token2 = strtok(token,":");
                token2 = strtok(NULL,":");
                
             
              
                
                //check the country
                if (counting == 11){
                  
                    temp = add_front(temp,new_node(token2,0));
                        
                        if (!isalpha(token2[0])){
                            char *token3 =" ";
                            token3 = strdup(token2);
                            
                             if(!isalpha(token2[1])){
                                temp = remove_front(temp);
                                token3 = token3+2;
                               token3[strlen(token3)-1]='\0';
                               temp = add_front(temp,new_node(token3,0));
                          
                             }
                        
                            
                        }
                  
            
                        
                        
                        }
                
      
                    
                
           
       
            }else {
                counting = 1;
                }
        
    }   
    skip_first = 0;
}

    
    while(temp!=NULL){
        node_t *transfer3 = peek_front(temp); 
        transfer3->word = transfer3->word + 1;
        if(ans_out==NULL){
            ans_out=new_node(transfer3->word,0);
        }else{
            ans_out = add_inorder(ans_out,new_node(transfer3->word,0));
        }
        
        
        temp = remove_front(temp);
        
    }    
    //remove all the space and " ' " case and add them in order
    char* now_airname = " ";
     node_t *final_output_list = NULL;
     node_t *transfer6 = peek_front(ans_out);
     int fin_dup = 15;

        while (ans_out != NULL){
            
            
             //printf("%s\n",transfer6->word);
             if(strcmp(now_airname,transfer6->word)==0){
                 fin_dup = fin_dup+1;
                 transfer6->duplicate = fin_dup;
                 now_airname = transfer6->word;
                 
             }
             else{
                 final_output_list = add_inorder3(final_output_list, new_node(now_airname,fin_dup));
                 now_airname =  transfer6->word;
                 fin_dup = 1;
        
             }

            ans_out = remove_front(ans_out);
            transfer6 = peek_front(ans_out);
              
        }
            final_output_list = add_inorder3(final_output_list, new_node(now_airname,fin_dup));

   
    //output them into a csv file
    FILE *output1;
        int j=0;
        int howmuch = atoi(nele2);
        
        output1 = fopen("output.csv","w");
        fprintf(output1,"subject,statistic\n");
       
         while( final_output_list!=NULL && j<=howmuch-1){
            node_t *check = peek_front(final_output_list);
            
            fprintf(output1,"%s,%d",check->word,check->duplicate);
            fprintf(output1,"\n");
        
            final_output_list = remove_front(final_output_list);
       
            j++;
    
        }
        fclose(output1);

}

void do_the_job3(char *Fname, char *q_num,char *nele2){
    /*
    this program will do the question 3.
    the program will take in the file name, what question is it doing and how many terms would it be printing on the csv file

    for this program, i created a new struct for this part. the structure of the struct is highly similar to the one you gave
    
    */
    char *line = NULL;
    
     
   
    ///////////////////////////////
  

    line = Fname;
    line = (char *)malloc(sizeof(char) * MAX_WORD_LEN );
    if (line == NULL) {
    fprintf(stderr, "Argh. Something bad happened with malloc. :-(\n");
    }
    

    
    char file_line [1024];
    FILE *data = fopen(Fname, "r");
    int skip_first = 1;
    int counting = 0;
    node_q3 *temp_q3 = NULL;
    node_q3 *new_node_for_q3 = new_node_q3("","","","");
    
    
    
    if(data == NULL){
        perror("error");
        exit(1);
    }
    //read in the yaml file
    while(fgets(file_line, sizeof(file_line),data)){
        
        
        char *token = strtok(file_line,"\n");
        char *portname2 = NULL;
        char *portcountry2 = NULL;
        char *portcity2 = NULL; 
        char *portshort2 = NULL;
      
        if (skip_first==0){    
           counting++;
           
            
            if(counting != 14){
                
                char *token2 = strtok(token,":");
                token2 = strtok(NULL,":");
                
                
                //get the country
                if (counting == 11){
                    portcountry2 = token2;
                    if(strstr(portcountry2," '")||strstr(portcountry2," \"")){
                            memmove(portcountry2,portcountry2,strlen(portcountry2)-1);
                            portcountry2[strlen(portcountry2)-1]=0;
                        }else{
                            portcountry2 = portcountry2+1;
                        } 
                        strncpy(new_node_for_q3->portcountry, portcountry2, strlen(portcountry2) + 1);  
                        new_node_for_q3->portcountry[strlen(portcountry2) + 1] = '\0';
                        
                    
                }
                // get the airport name
                else if(counting == 9){
                    portname2 = token2;
                    if(strstr(portname2," '")||strstr(portname2," \"")){
                        memmove(portname2,portname2,strlen(portname2)-1);
                        portname2[strlen(portname2)-1]=0;
                    }else{
                        portname2 = portname2+1;
                    } 
                    strncpy(new_node_for_q3->portname, portname2, strlen(portname2) + 1);  
                    new_node_for_q3->portname[strlen(portname2) + 1] = '\0';
                    
                    
                }
                //get the airport city
                else if(counting == 10){
                    portcity2 = token2;
                    if(strstr(portcity2," '")||strstr(portcity2," \"")){
                        memmove(portcity2,portcity2+2,strlen(portcity2)-1);
                        portcity2[strlen(portcity2)-1]=0;
                    }else{
                        portcity2 = portcity2+1;
                    }  
                    strncpy(new_node_for_q3->portcity, portcity2, strlen(portcity2) + 1);  
                    new_node_for_q3->portcity[strlen(portcity2) + 1] = '\0';
                       
                }
                // get the short form of the airport 
                else if(counting == 12){
                     
                    portshort2 = token2;
                    if(strstr(portshort2," '")||strstr(portshort2," \"")){
                        memmove(portshort2,portshort2+2,strlen(portshort2)-1);
                        portshort2[strlen(portshort2)-1]=0;
                    }else{
                        portshort2 = portshort2+1;
                    } 
                    strncpy(new_node_for_q3->portshort, portshort2, strlen(portshort2) + 1);  
                    new_node_for_q3->portshort[strlen(portshort2) + 1] = '\0';
                    
                }
                else{
                    
                }         
            
            }
            else {
                counting = 1;
                
                
                temp_q3 = add_end_q3(temp_q3,new_node_q3(new_node_for_q3->portname, new_node_for_q3->portshort, new_node_for_q3->portcity, new_node_for_q3->portcountry));
               
            }
                
       
    }  
    

    skip_first = 0;
    
    
            }
            //let the string become the format in the tester 
            temp_q3 = add_end_q3(temp_q3,new_node_q3(new_node_for_q3->portname, new_node_for_q3->portshort, new_node_for_q3->portcity, new_node_for_q3->portcountry));
            node_t *ans_out_q3 = NULL;
            while(temp_q3!=NULL){
            node_q3 *strcomp = peek_front_q3(temp_q3);
     

        char *correct_name = strcat(strcomp->portname," (");
        correct_name = strcat(correct_name, strcomp->portshort);
        correct_name = strcat(correct_name,"), ");
        correct_name = strcat(correct_name, strcomp->portcity);
        correct_name = strcat(correct_name,", ");
        correct_name = strcat(correct_name, strcomp->portcountry);

        ans_out_q3 = add_inorder(ans_out_q3, new_node(correct_name,0));

        temp_q3 = remove_front_q3(temp_q3);
    }
   



    //add those name in order into a linked list
     char* now_airname = " ";
     node_t *final_output_list = NULL;
     node_t *transfer6 = peek_front(ans_out_q3);
     int fin_dup = 15;

    while (ans_out_q3 != NULL){
            
            
             
             if(strcmp(now_airname,transfer6->word)==0){
                 fin_dup = fin_dup+1;
                 transfer6->duplicate = fin_dup;
                 
                 
             }
             else{
                 final_output_list = add_inorder2(final_output_list, new_node(now_airname,fin_dup));
                 now_airname =  transfer6->word;
                 fin_dup = 1;
        
             }
           
            ans_out_q3 = remove_front(ans_out_q3);
            transfer6 = peek_front(ans_out_q3);
              
    }
    final_output_list = add_inorder2(final_output_list, new_node(now_airname,fin_dup));
    // print out the linekd list to the csv file
    FILE *output1;
        int j=0;
        int howmuch = atoi(nele2);
        
        output1 = fopen("output.csv","w");
        fprintf(output1,"subject,statistic\n");
       
         while( final_output_list!=NULL && j<=howmuch-1){
            node_t *check = peek_front(final_output_list);
            
            fprintf(output1,"\"%s\",%d",check->word,check->duplicate);
            fprintf(output1,"\n");
        
            final_output_list = remove_front(final_output_list);
       
            j++;
    
        }
        fclose(output1);
}
    





   

void data_process(char *argv[]){
    char *file_name = argv[1];
    char *question_number = argv[2];
    char *num_element = argv[3];
    
    file_name = strtok(file_name, "=");
    char *fname2 = strtok(NULL, "=");

    question_number = strtok(question_number, "=");
    char *q_num2 = strtok(NULL,"=");

    num_element = strtok(num_element, "=");
    char *nele2 = strtok(NULL,"=");
    

    if (strcmp(q_num2,"1")==0){
        do_the_job1(fname2, q_num2, nele2);
    }
    else if (strcmp(q_num2,"2")==0){
        do_the_job2(fname2, q_num2, nele2);
    }
    else {
        do_the_job3(fname2, q_num2, nele2);
    }
    }
    





/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    data_process(argv);
/*

    // Initial dummy code
    char *line = NULL;
    char *t;
    int num = 0;
    node_t *list = NULL;
    line = (char *)malloc(sizeof(char) * MAX_LINE_LEN);
    strcpy(line, "this is the starting point for A3.");

    // Creating the nodes for the ordered list
    t = strtok(line, " ");
    while (t)
    {
        num++;
        list = add_inorder(list, new_node(t));
        t = strtok(NULL, " ");
    }

    // Printing out the content of the sorted list
    analysis(list);

    // Releasing the space allocated for the list and other emalloc'ed elements
    node_t *temp_n = NULL;
    for (; list != NULL; list = temp_n)
    {
        temp_n = list->next;
        free(list->word);
        free(list);
    }
    free(line);
*/
    

    exit(0);
}
