/*
*  Levenshtein distance is a string metric for measuring the 
*  difference between two sequences.
*  the Levenshtein distance between two words is the minimum number 
*  of single-character edits (insertions, deletions or substitutions) required 
*  to change one word into the other. It is named after the Soviet mathematician 
*  Vladimir Levenshtein, who considered this distance in 1965.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include "../../config.h"

#define MIN(x, y, z) ((x) < (y) && (x) < (z) ? (x) : (y) < (z) ? (y) : (z))

using namespace std;

// test data
extern vector<string> random_s;

VIP_ENCUINT EditDistance(vector<VIP_ENCCHAR> &str1, vector<VIP_ENCCHAR> &str2){
    VIP_ENCUINT dist;
    unsigned i, j;
    unsigned strlen1 = str1.size(), strlen2 = str2.size();
    vector<vector<VIP_ENCUINT>> edit_matrix(strlen1+1,  vector<VIP_ENCUINT> (strlen2+1));

    if (strlen1 == 0) dist = strlen2;
    else if (strlen2 == 0) dist = strlen1;
    else{
        for (i = 0; i < strlen1+1; i++) edit_matrix[i][0] = i;

        for (j = 0; j < strlen2+1; j++) edit_matrix[0][j] = j;

        for (i = 0; i < strlen1; i++ ){
            for (j = 0; j < strlen2; j++ ) {
                VIP_ENCUINT edit;
                if (str1[i] == str2[j]) edit = 0;
                else edit = 1;
                
                edit_matrix[i + 1][j + 1] = MIN(edit_matrix[i][j+1]+1, edit_matrix[i+1][j]+1, edit_matrix[i][j]+edit);
            }
        }
        dist = edit_matrix[strlen1][strlen2];
    }
    return dist;
}

void FindDistanceWithinArray(vector<string> &arr) {
    // unsigned len = arr.size();

    for (unsigned i=0; i<5; i++){
        for (unsigned j=0; j<200; j++){
            // prep the input data
            vector<VIP_ENCCHAR> arr_i(arr[i].length());
            for (unsigned k=0; k < arr[i].length(); k++) arr_i[k] = arr[i][k];

            vector<VIP_ENCCHAR> arr_j(arr[j].length());
            for (unsigned k=0; k < arr[j].length(); k++) arr_j[k] = arr[j][k];

            VIP_ENCUINT ed = EditDistance(arr_i, arr_j);

            cout << "INFO: edit_distance(" << arr[i] << ", " << arr[j] << ") == " << VIP_DEC(ed) << endl;
        }
    }
} 

int main(void)
{ 
    //Convert data to VIP_ENCCHAR
    vector<vector<VIP_ENCCHAR>> arr;
    for (unsigned i = 0; i < random_s.size(); i++){
        // prep the input data
        vector<VIP_ENCCHAR> str_i(random_s[i].length());
        for (unsigned k = 0; k < random_s[i].length(); k++)
            str_i[k] = random_s[i][k];
        arr.push_back(str_i);
    }    


    {
        Stopwatch s("VIP_Bench Runtime");
                int L = 3;
        for(unsigned j = 1; j<L; j++){
            for(unsigned i=0; i<=random_s.size()-L; i++){
                VIP_ENCUINT ed = EditDistance(arr[i], arr[i+j]);
                cout << "INFO: edit_distance(" << random_s[i] << ", " << random_s[i+j] << ") == " << VIP_DEC(ed) << endl;
            }
        }
        // FindDistanceWithinArray(random_s);
        cout << "Completed analysis of " << random_s.size() << " strings" << endl;
    }

    return 0; 
} 

// tuck the test data at the end of the file
// Each row is 80 characters!
vector<string> random_s = {
    "CGCCGACCCATACTGGTCGGATGCTCACTCAGTGCAATGATAAACACTTATAGGATCGCATAACTCCAGAACATTAGGCGCGCCGACCCATACTGGTCGGATGCTCACTCAGTGCAATGATAAACACTTATAGGATCGCATAACTCCAGAACATTAGGCG",
    "CGCCGACCCATACTGGTCGGATGCTCACTCAGTGCAATGATAAACACTTATAGGATCGCATAACTCCAGAACATTAGGCGCGCCGACCCATACTGGTCGGATGCTCACTCAGTGCAATGATAAACACTTATAGGATCGCATAACTCCAGAACATTAGGCG",
    "TTTCGGGTGAAACGTATTCTGCAATGACCTCTTCAGGTAACTGTTGGGTAGAGATCTCTTTGTATTGACAGGCGAGAATCCCCTAGGGAAAAGTTAAAGATGGCCGAGGGTAGGTCAATCAACGTCTGCGGTTAGTCTGTTCGGTCGAGCTTAGTATAAC",
    "ACTTGTAGACTGACGCTATTCTGGTACCCGCTACTGCCAGATGTAACCACTCTGCGACACGGTGCGTGAAGATTTTGAGACCAGTCCTTTATTCATGTCACTGATAGAAATCACTAGTGGTCGTGGTGGTTCGCACGGCACCGCAATTAGTCGCATGTCT",
    "GACGTACCTGAGAAGGCTGCCGCTACAGCAGGACATGCATCTTGACTGGAAATGCATTGCGCAGCCCGCGCTTTAAGCGTCCAACCGAACGCGCTAGTGAAGTCGGTTCATGACCGTGATGTAATGAATCTCTAGTTCATCGACTGAGATATATGTGATT",
    "TAACTGTAGACTGTCCTGCGAACGTGCGATAGTCGTGACGTCGAGCACCACTGAGAGGATGCGGGAACACCCATAATCATTCCCGCGATTGGGAACAGGAGAGGCGCTCAAATAGGGTGCGCATTCCTGTTCTCAATATAAGAAAGTTCCTCTGTGACAG",
    "GAGCGTGCATGAGAGCGTCGTGCCGAGGGACCGTGAGAAGACAACAGCTTTCGAAGGCGACGAGCTTACTCGGCAGTCCGACTCGCATAATAGGCGCCGAAGAGTCTACACCTAAATGGCTACCAACCTATAATTCCCTTATTCGCTCGGGTATACCGAA",
    "AAACGCGAGGTGCGTTTCGGATGATGATCAGCGTTGTCCGTATATGTCTCGGGCTTCTATAAGGCCACTTATGTGTTTCTTCATAAGCGGTGGATTGAGCTTTAGGCCGGTGGAGCGCGTGCGTCCCACAGTAATTTTGGGCGGGGCGAGCGCCACAAAC",
    "TGGGATTGCAAGAGCCTTATGCTAGTCGAACTCTTCCTCGTTGAAGGATTGCACAACTCACAAATAACCTAAGTTTTTGTCTAGTCAGGGGATGAGGAACTGTTACCCTTCGCCTAGCAACGACTAACGAGCACCAATAAGCCTGAAGTAGACTGCAGCC",
    "TGGAATCGACAGCGTTAGTGTCCTACGCCGAGCGCGGCACGATGGAGTCCAGAAAAGGGCTCTACGGACAGCGTCCGTGGCTAAAGGGTTTATAGTCCCAAGAGCTTTACTATGGGCGCATCTTTAGTGCTTGTCGGCGTTACGGAGTGAAATATGTTGT",
    "AGACTAATTCAAGCAGTCAGGCTATAAACTGGTCACAGGCTCACAACTCTATGAGGTAGTTTATAATTTTTTCTTCGCTCACAGGAAAGCGACGCACCGTCAAACCAAAGTTCAATACAGAGGGTGATTGTAGAGAACCCACCTTAAGTGGTTGGCGCGG",
    "CCTGTCACAGGCACGGCAGTCAAAAGCCAGCACACACTTAAACTACCAAACAACCCCTAGGTTGGGTACTCGAACTATTAGAGTGGTTACACTGGTCCGGCTGTTGTAGTCGAATGTTGTACTCCGCTCTCCAGACAAGAACGCAGCAGGAAAGCAGTCC",
    "AATAAACGTACGCGACTCATGGTCGAGCTATGACTATACCAGCAGAACATCACCGGAGAGATAAGACAAAGTTCAGTAGGCTCCTGCGCCTCTTAATGGCGGAGAGGTATCCGATGCTCAGGCACGGCAAGCTTGACTTTGCTCAAAGGAGGGATGGATG",
    "AGAGGCCCCCACAAAAGTATTCGCTCAGCTTTCTTACCAAGGCAAGTCTAAGGAATTCGGATCCGGCTGGTCCGTGAGGGCGTTTATGGGTTGACTAGTAGCTTCCCGAGTATAACGGACGTGTTACATATAGAGGCATTTAATGAGAGGACTAGCACGA",
    "ATGCTGCTGATCTACATCCAACCAACCCCGCACCACGCTTAAAGATTGCTATTCGGCGTACACGACGCTGGCCACCCATGACCAGCGAGACTATCGGCCCCAATTATGATACACTTGGCTGATATCCAACACCAGACAAATTATATATCGACACGTTACT",
    "CGCGGCACACCTTGCCGTCCCGACAAACCTCTTATTGCGCTATAGAGCAGATGCACGGGAATCTTAAACATCTACCTATCTTCTTCCCAATGCGGTAGCATAATCTTCACAGCCACGGGTAGAGCTCCCTTCCACGGTCGCACTCGACTCTAACGGTAGT",
    "TTGGACAAAATCCTTGTTCCCTTTTAGTGACCCCAAGGGAATAATGGTTATCCTATGGCCAACGCCGCTCAGACGAGTGTTAGTATAGATTTAGGCGTAAGAGGCTTCTGAAGTATGTACAAATTGTGATCCATCTAAGGATGCCAAACTGTGTGTCCGA",
    "AGCAGCCTAGAATCGGCTCATCTCAAGTACCGATAGAAAACCTATTCACGGACGGCCGCCTTACGAAGAAAAGCATATCCCAGAATCTTGGCGAACCTTTCGATAAAATAGACTGACCACACCTAATCCTTCACCCTCAATTGTCCTTGGGCGAGAAACG",
    "CGGAGCGAGACATGTAGGTAGCCCAAGAACTAGCTGTACCGATACGGTAGTTCAGTAAGGTCAGCACCAACAGGCTATCGTGATAGTCGATTTCATGAACCCCATCAAAATCGGGAACATTATAGCGTCGTCAACTATCTGCAGAGGCCGACACCCACGC",
    "TCAAACGTGGAAGCACATCTGGCTTGCGAACTCTAGTAGGAGTAGAGTGTAAATACCGTCACTGAAGTTACATCTGCCACGGTGAAACGGGCTAGGTAAGGTATTAAGGATCCTGAGGGTCACGTAATTGAAAACAAGAGAGGTTGGGGTACCTTTCGGT",
    "TTTCCTTATCTGGCGTAGGCAGTGTTCTACGAATTCACACGCGCTGCCGAAGCTGCCCGGGAGAGCGGGACCAATAGATTACTGCGCGTGGCTGGGGCAGTGAGATCAGGATCTCGGGTGAAGGCAAACGGGTGGAGCCAGTCGGTCTGGTACCGACGCG",
    "CCCAGCTGTCTTCGCTACTTCAGTACAAGGTTACGCTCAGGCAGCTAGGCCCTAATTAGGGGCCCAAACTACGAGCAGGGCCTATTCTTCCGGTCAGCTGGCCCTCCGTACATCCGTGAATGCATAAGCTACGACAGGACGAAGAATAAATGTTGTCGAT",
    "CGTTCTTTACGGGATCGTGGTTGAAAGTTACCAAATTAGCTCGATCAAACCAGCCCCCCTCTAGGCGCGAGTCCATCTTGCTGTAATATGGGGCGCTGGGAAGACTGACATTTCTGTTTCAAGAGTTATTCTGTCTGGTAGCTGCGACGTGACGGGGTCC",
    "ACGATATCCCGGTGACTCGGACCGAGGGGCTCGATCTTGACCAATCCGTCAGGGGCTAAGTTGGCCTTCACAAGGCATAAGGAAAAAAATCGATATAGTGCTCTCCACGTCTGGCGCAAGAGCCCTGGTATGTACTGATCTGAAAGTCGACAGTCAATGT",
    "GTCCTGGCTGGAATGTTTTCTTCGTCTACTGATGGCTCGGTACCTGCTCTATTCTAGATCTGTCTCCGAAACGAGAAGTCGCGCCTCCCGATTAGTTTCTGGTAGTCTAGACCGACATCGTATTTCCCGAGACGGGATCAACCCGTCTTCGGAAATGCTT",
    "ATACGCAACTTTCCAAATATAGACCCCATGAAAAACGTCGCAGCCAGACGAACGTCCTATCGGAGTCAGTGCTGCCGAGATCCCCTGAATCTATAGCGGGTCCTGGCACCATGGACCACCATGTCAGGAGCAGTCTAGCTATGAGTGATTATCGTGAGCC",
    "AGCCAAGATGAAATACAGGGCAGCATTTATGATTCAGGCGACTACGAGATGGCATGGGCGCGAGATCCGGTTCCTGCGCAATACAAGAATCGCTATGATATTTGTGCGTATCGAATCCCTATTTTCTCTACGGCTAGGGGGGACATAAGCGCACTTATTG",
    "TTGTAAGACAACGTTCATTTGCGATGGAACCGGCGCATGGTTGATAGGTTAATAAAGAAAGACGCGATCAGTTTAGTTCTTTGAATCTTACTAGATGCACCACTTATGAAGAAATCTACTTGGGCCTCATATATTAACCAACCTTATCTCATTGGTTCGA",
    "GGCTTCCGTTTTGTAGGCGGGCGAGTATGTCAAGTTATGTGCAGAAATTGTACCCTGGGTGTTGGAAACACAGGGTGTAAGTCAGGCTAATGTCCGAGTAAATAGAAATAACCGCGATTGCAGGAACGGGTGCTCGCTTGTCCAAAAACTATCGCAGTAC",
    "GCTTTCCCACCAATCGCGAATCGCGATAAGGATCAACTCTATCCTACACTTATGTCCTCTAGTATCAGACATCACGAAGTTAGGTGCGCCACCCATTGTTCGCCGACGAGAGGCATGTAGCAATTGCGATGCCTCATCGCGCGCCTCTATTACGTACCGA",
    "CGGTACCTGATTAAATGACTACAGCGGATATGTAAAAGAGAATCGTTCCACGGTACCGCTACGTATCCGACATGATACTCAGAAGACCTGGAGCAGCTCTAGGGCAGCCACTAGGCTCGCAAGCGTATCATCCTCCGAATGACGCCTATGATGGCGGAAG",
    "GGACGGTCGCGACCAGTCGGAAAGAGAGGTCATTATTATTGCCACTGCTCAATGGAAATCAGTATTGCTTGCCACACAGAGGGCGTCTCATATACGAAGGGCAGCTCAGATCTGACGCGAAAGCCCACGACCAATCGCAAAACGGCATCCTTTTTGCTAA",
    "GTAATGCGTCATCGGTACCGACGCGGCGTGAGGACTAAAACCGCTCAGACGGCTTACTGAACAAACTGTGTCATCGTCATAAGGACTCACTCACGAAGACGTATATGGATGCTGGGTCCGATTGTCGTCTAGGAAACAAGAGACTGGGCATCTTTAATAA",
    "CAATAGTCACTCGAGATCTGACCTGATGGGCCTGGTTTGTAGTCGCTGTTGGTCCCGGGACGACAGCCCGCGAGTGGATTACCAGAACGTGCATAATTTCTTACTGGTGATATTCGTGTACACTCGCACCCTTCCTTAAAACATCGCCGGTAGCGCCTCG",
    "ATCGCCCGCAGCTTTCACTTAAATCAGGGTCAATTAGCCATTGCCTATTACACTAGTCCCCGCTTGCCCACCAGAGATGGCTTATGCGTATAGTTCGATCGGAGAAGCCGAAACTGCGCCTGACAGCCGAAGAACAGCCGGGCGTAAGGCCGTTTATCCT",
    "CATAATTGTTTCTTATACGAATGTACCATCGTGGATTAGAAATTAAACTGTGGTCTTATAGTAGAGCTCTGCACTGAAATAAGGTGAACTGGTGGTAAGGTAGTACTCACGGAACGGTGATTAACTCTGGGCCGGGGGTCGACTCTCGCCCTGTCACCTC",
    "CAGTGCTGCTTGTGATTGCGACTCCTTCTAGGCACGTGATCTGAAGGATGCCGCTATAATGTTACTGCTAACCATGAATGTTATTGCATATGACTCACGCATGGAGCGTGACAGGTATTTAAAACGGACATAGAATCAATGAAGCCTCTGATCGATTGCG",
    "GACCGACACCAGATTGTGGGTTTCAAACGAGACTGACCAGTACTCAGTGCCCTAGAACTGTCACCGGTGGCAGTAATACGCGACTACACTCCTGTCTACTGGTACATTACTTGTCATGGTAATGATACGTTCGAAGATTGTTGCGCCGCGGGAAAATCGG",
    "AGCGCGGCGACTGCAATCATAGTACGTCATAGGAGAACAGTAGTGAGGGCACAGCAAGAGGAAGGGCATCCTAGGATACTCGCTCACTGCAACAATTGTCGAGACCCTGCAACTGTTCCAATAGATATACTATGTTAACTAAGTTAAGCCATTTGGGACT",
    "GGCCAATATACGACCTTTCATGGATTTTGCCATGGCTCCGGCCTTGGCGATGAGACTGACCAGCACGCCTTTATCACGAGCGCGTATACATTTAACTAGCCCGGCCTTACCCTTTTACGCTGTTGGCTAGCGCTCCGCGACGAAATGGACCGGTTTAGGA",
    "GGCACCGGGGCTGTTCGGGGGACTTGCGGGCTCTGAAAGACCGGCAATATCCGGAATGTTTACCCCGCTAAAAGAGTGTTTTTGTCTTCTAAAGCGGAGGGCCAAGGAACTTCAGTTACTGAGATCCTACACAACACGCGCGCGGAGCCCTGACCACTAT",
    "GCTTGGCATGTCAAGCGCCTCACAGGAGGCCGATCAATACACGTTTCGCCGTAATAGCTTTGGATACATGAGCGGTAATGGTTACTGCCCTCAGAACCTCTATTCGCCGAATTTTCTCCCACACTAATATGTGACACTACCATTCGCAGACGTGCAAGTC",
    "GCTTAATCAGGCTAAAGACGGTTAGAGAAGAAGTCGTACTTAAGATACACACGGTGGAATACAAAATTTCCCATTAAGAGTATCGAAGTCGCATGGCGAGTTAGTCGGGCTGGAGGTTTCTGTTTGGTGCCAGGATTTAAAAAGCTTTTATTTGATGATT",
    "GTGGGTGTACAATAGGCATCAGATGTTTGTCGCGACGGCAGAATAGGCCTCACGAAGTGGCGGCCGTTTTCTCATAGCGACAAGACTACGAATAGTAACGAATACTCACATGCAAAAAAACATGGGCAAAATCGTTGGCTATTTTTACCCACCATTGAAT",
    "ACGGTAGATGATCGACACAGCGTAGCAGTACTTGCTCTCAGTTATACCGGCCACCTAAGCATTGGGCCAGCTAGGCCGAGCCGGGATAGCGCTATGCATACTCGGATCGTCCGCGTTGAGTCTCCCCGAAACACGTGTACTACGTGGCTAGATCCAGGAC",
    "CAGCTCCGACTGCCTTTACATAAGGTATCCCCGGTCTGTCGGAACATATATACAGATAAACCAGATCTAATGTTCGGGCCCTAGTGCCGGACTCGAACTGGAACGGTATTTACAGAAAGCGCTTCCGTATGGTTCTCCTCCCCCCACCGGCTATACTTTC",
    "ACGTTTGGTGTCAGTGGTGGTGCACGTGTGTCACTTGATTAGAGGCTTCCCGCGATCTTTGGGATCGGGCAGGAGTCAATTAAACGTTCTTGAAGTGTTGTTCCAGGTTTCCCCAGGCTGGACGCGCGTCGAAGTACTCTGCCCGTCCCGGTGGCATTAG",
    "CACGCACGCGTTTCCCGCCAATTCGATAGTGTGTTATCCGGCTTGTCCTGATACGACATATTATAGAGCTTGTCCCCGGAAAAGATGAATATGGCAACACGAACCTAGAGGCACCCAGCGCCCCAGCGCATGCTGTGCTCTCCCTACGACATAAATGATT",
    "ACACGCTCGGTGGAGGTAATCTATTCTCCAGCAAAGAGCCTTACAATCAGTTATTAAGCGCCCAGTATTCGAGCAACTGCGCAACTTTCATCTTCCCTAGCGATCGTGACGATAAACGTAGCGCTCGCGTTGGTTAGCGAGAATAGTGGGACGATAAATA",
    "CTACAGCCACGGGAGTTTTGCTCAGCCGAAACAGCACTGCTGTCTAGACAGCACCTGCTAAGCAACTTCAAACTCGGAGTAAAAGGGGACTTTCGAGAAATTACAAGCCCTACTGTACATAGTAGGTGGGAGAATCTACCCTGGGACGCAGTCCAAGATA",
    "AACCTTGGCGTTAACTACATCTATGCGTGGCGTTTGGAACTAGTGCCTGACTGTCTACGAGCCCATCGTACCACACCTTCGCCAATCTTCTATCCGGTTGGCAAGTTAACCAAACTGCCATCCTAAGGACGGTATACGAGGAACCAAGTAAGTGCCCCCC",
    "CCAACTCACGTAGTAGCATAGCTGGTCACCGGCGGTAGTTCACACACAGCGACCTCAGATGCTGGCTCAAAGTTAGCACGCATTCGGCATATGATCTCTTATAGAAAGTTGTCTTTTTGCACCTTGCCCTATCCCGTGGTTCCCGGTTGGGAACATGCAA",
    "TCAAAAATTCCAACTGGAGCTTAGCGAGCGGATTACCGCTGTCATGCTCTGTATTAACCAAAACTTGTCGAATGCGACGGGTGGCCTTGGACATGAAACACGGCACGCCCAGGTTTTTCCTGGGCCATAATAGGTCTACCGTCAAGCGTTTTACGTCTAC",
    "ACTACCAACTACAAACCGCGAACTCAGGCGTGATGCGGCGTATGTACCCACTAGATTACTACAAAGTTTAGTTTTTGTACCTGACACGGTTTACTGCATCCGAATTATTAACAATTGAACATGAACCGCGCACGGGGCAACACAGGGCATGGATTGCCGA",
    "AGATTTTGATTAAACTTTTTCGGATCTTATCGCTAGGCGCGTAGCGTAGGGCAGATAGGGTCAGCTCCGAAGTCACCCTTCGGGTTAGACCCATCCAAACTGCTCGATTCCGAGAGGGTACCGCGACACGCTTGCGACCGAAAAAAACGAGACCCAAGCG",
    "TGGTATCTCCAGTATCACCCGCTGGCATATGGCCTATGTCGGTGCAGGGTCCTCAAGACCTCCTAAGTATTAGTTACCCTCTCAATATATGCATATTTGCCTGGTAACCGAGCAGCCACAGCTCCCCCGCTTGCAAGCCACCAGGCCTCATCCAACTCCA",
    "TGACGTTCGGGTCAAGCTCTGGCTGAGCTTCCGTGGTCGTATCGCTTAATGAGCAATAGAGTTTTTAACAGTACTAGTCCACTGATCGCAGTCAATCCGCGCTCAACAGTTAAGCGACTAGGCCTGCGCAGAGCACGGTACCTCCAAGTCAAACTCTATA",
    "TAGCATGGCCTTGTTATGGGGGTCGCCCTTTATTGTGAGGAACATCATAACACAGAGCGTAGATGAAGGCACGCGGTTGTCTGTCCTGTCGCAGCTCTTTGGCTCTTGTAGACATGTTAGGGTCCTTCATCCCTGGAGGGGTACTTTGAGATTGCAGACG",
    "GTGTCAGAATCAGCATGCTAGCGCCTAGAGTTCGTGGGGATCAGCCGGACACTCATAAGACACGATTGAAGCACCCATTTGCACTGTATGTTTCCTCGCGACTCATCTGCAAGCATGCACTTTGAAGCTTTCTGGAGTAAATAGGACGGTTCTCTCACTC",
    "TGGATAAGTTCACGATGAGCCGCAAGTTTCACTGGGAACTTACTAATACACAGCTATGGGCTTTCCCTTTTGTAGAAGCTTCTGTGCCTCCAGTCTATCACGTCTTTGCTACCCCATGGTGCAACGCGGCGTTCGTGCGACCTTGGATGTGCCGGAATCC",
    "TCTGCCTTCTCTACTTCAAAAATTCTGGGAAACACAACAGAAACCCTCACTTACTAGGGTGGAGGGGCCGAGAGGACATGCAAAATTTCGGTTATGCTGTCGGCAGATAAAAGACAGATTTCTGGAAGATTAGCTAAAGGGTTCTCTTCGAGCGGCCGAC",
    "TACGAAGGAGATGTCGTAGAGCATATAGGCCTGGAAACAAAAGGCCTAACTGGTAACTAATACGCCGAGGAGCGCGCTGAGTCGTAGCTTGGTTTATGGGCACAGTTGCAATTGACCGAGCCTTGATGACCCCGTACAAACCATCCCTAGTCTCACATCA",
    "CGAGAGTTACAACCAACCAACGCTCGAAGACGAACACTCCACTCGTAGAGCAGGCGTAGTGCAAGGGGACGGTGTTGCACGAGTAGACTTGGTGCATCCAGCCTCAACGTATGAAACAGAATCGGTGAAATACAGGTATGAATTTCGACAATTTAAGGTG",
    "GTTAGCATGAGCCTTATGAATCCACTGCTCAGATTTGTACAAGTATTGCGCCACGACCGTACGCACTGCCACACTCGTAAGCCACTGTGTGTAGATAAGGCTACTGAGACGGAGAACACCACAAATGTGGTAATGGCCAAATCGCAGCGTCGGGTATATT",
    "ATTAGCGCGGAACTTGATATGAAAGTAGCTGTCGTCGTACACCACTTACTATAACGTACGCAAGTAAAGGGCAAGCAAGGCTCTCTTCGAACAACGTCCATGAGGCGAACATGAAGTAGTCCCGCTACTCTCGAGTCTTCCGCCCAGCACTGTAGTGGTG",
    "AACCTCGACGGGAGCACAATCCTTTATGGACACGCACCAACGCCGATCCCGTGACCAACGCTGAAAACTCATACTCCTTCGAAACGCAACTAGGACGTAGCGATGCCTGGTCATTTCAGATTAGACGGACGTCTACCGGGGTAGCCCCAGATTCGCTGAA",
    "ACACCTGTTCGTACATATCTACCCCTTCCAACGCTGGGGATCCTTCCAGCTTCGAGACGTGGATTCCCCAGTGGCTCGTACCCAGGCGAAGGGCTTCGCTATGGTTATCCTGGTCGGACCCTACATTCTCTCGATCGAGCTGCACTCATTCGTCAGCATA",
    "CCGATATCTGTGGCACTTGCTGTGGGAATCGCGAGGTTTGTAAAATTTCCGTTATAACAATCAACTTTGTCAGAACCCTCGCAAAGCGCGCTAGATACCCGATATTATGGCAGATTCTTCCCCAGAGCTCGCCGTTTAACCACTTACCGTGGAATGTTTC",
    "CCCGGGATCGAATATTCGGTATGCGCAGCCGTCAACTGGCGCAGAGGTCGACTGTCCGCTCAAAGCCTGAGTTTGAACGCTGTAACGTTCTAGGACACCCAACAAATATCCCGATGCTTGCACTTACCGTCATGGGCCCAGATATCACGTCGAGTCTTCC",
    "CTGCGTGATACGCAATCGATACCGACTACTTCGGGATAACAGATCAAGGAAAGTATTTCCCAGGAGGAGTTCCGCATGCAGACGAGGGGCTCATTTGCTAGTTCACTATATAAGGTTTCTAAATGAGTCAAAACATCTTATTTAGCGTCAACTTGGAGCA",
    "CTTGCACACGATTTTGATATCAGAGAGGTGCACTCGTAGTGCCTGTCACTACAAGACGCACTTTGGTAAGACCTACAATCAAGAGATCTGCTTCGCAGAGCTTGAATTCTTTAGAATGGCTTAAAACGGAAGGGGGGACAATGACAATAACGGGCAGGCC",
    "TCAATTACCGGATCCACTTGGGTGACCCGTGGGCTAACACACATTAACCATTGAGTCTATCCACTTTTGGCCTCTTAGGCGATGGCCAGGGGCCGCTTTGTAGGGGCACTAGAATATGGCATGAGTCCATCGCGAAGATTATACGAACCCACACCTATGC",
    "AATAGGGCCCTCGCCAACCTTGTGCCTCAGCAATCCAGTGCCACCACACCGTTTGGTTGTTTTAGACCCGCTTACGCAAGAACAGCTATTAGAATGACTCATTTGAATGGAGAGGTATCCCAAGTGCTTTCGCAGTATACAGCATGATTCTTGACAGGTC",
    "GTGCCCTATAATTTCACGCGACATTCGGTGGAGTCTACTGGGTAACTTAAGCCGATCCTTTCGAAGAAGATCTATAATTGCGTAAGCGAATCAGACGTACACAGAAAATGGTTGACCCGGCCACTGAGTATATTCCGTTCTCCGTGATGAGAAAAATTGC",
    "ACGAATCGCGACTTTGGTCTGGATGCCTGCGCTCGTAAGTACTATGCCTCTGCAGGGATTCAGCCTCTTCCGCTGGCACTCGAACTGCGCAGTTATGACTACTCCTAAACGAATATCGGCGCGGCAGGCGACACTGGGAGTCCGATCATAATACACCCAG",
    "TGGCGTCGCAGCGGCCTAATAGGGGTAAGTGCCTATCCTATCGAAGCGTCTAGGCGCGTCCCATAGGAGTGTATCGGGTACGAGTTGTACTTGCTGTATGTCATAATTCTATGGGAACCCAAAGTACAAGCAAGCAGACCGCGCTAATATAACAATCTTG",
    "AGTTATTCCCGTCTTCGTACAGGATTCTGATCCGCTATGAGCCCGTGTGCTAATGCACATCACCGAAACCGACTAACTTTACCCGACTAGGAACGCTGAGGTCTCATGGGACGCGTCGAGCCGCCGTGGTGAGAAGTTACGCCTTAGCGTAACTTCCCTC",
    "AGTAATGTCAAGGCGATAGACAACACAGCTAGTGTCGTGCCAAGTTGCATGTAACACCTATCTAATGAAAGCACACAGCGCCACCGAAAAGTGAGTCCATCACGAAGGTATCCACTTGGCTCGCCAAGATTAATTACTCCACCGTCTCTATCTCCATCGG",
    "ATTATCCACCAAATCCGAAATTTGCTAAATACCAGCCTCGCTTGGTCAGGACATCTTACTTCCTAATGTCCAGTGTCCAAAGGCAGCATGGTCGTACGGGACTGGTAGGCAGTCGGAATATCGCCTAAACCTCGCTTGCTCGTGTAATTAGTGCCCGATC",
    "TAGTGCAGAGCGAGGTCAAGAAGTTGTTGTGCTGCCTAGCTCTTAGAGCCTACTAGCCGATTGGTGAGCATTCCGGGAAGTCATAGCCATATACCCTCTGTCGCCTCTGAGGTTACGCAGGTGGCCCTACCATCCAAGACGGCTGGCCCATGACCCTGGA",
    "TTGGTATACCATGATTAGCTGCCCTAGTCGTGGAAAATAAACCTCACAGAAGTCCAATAGAAATGTTATACATGCCCGTGTCGCGTGAGCCTGCCTGACGGGGATTTGTGGACTTGGGTACAATCATCCGTGTTTGCCATAGTAGATTTACTCCTTCCCA",
    "GTCCACATATGTCGGTTAATTATCTCCAAATCACCGGTTAGCCAGGGGCGGGAAACAGATTGCCGGCTTCGTGGGCGAGTCTTGTCGAAAGCAGCCAATGGTAAGTCTGCTCGGAAGAGATAATTAATTGTAAATAAGCCAAGACCCGCCGTGAAAATGC",
    "GCTGTGACGTTTGAGCACTAGGTTTAAAGTGACTACTCACAGGAAGTTCACGTCTTAACACACAAAAACAACTAGGAACATCCGGCAAGCCTATAACACTAATTATTGCTTCGCAAAGTAGTGAAGGCTTTTTGCGGGGGGCGTCAGCATACTCCGACCC",
    "AATGGTATAACGAACTGATGACTCCGATCTCGACGCGTAGACCATAAGCAGAGATTATTAAGAAGACTTCCTTACATCTGGATAAGTTGAGATCAACTAAGTGATTTTCTGTACACTGTCTGAGGTCATTCCAAGGGCTAGGGCCAACGCATACGGATTA",
    "GTTCATCAACTACACAGGGGGCCTGTGGAATCACTTATCCGGGTTGAGAGGCCGAACATCATCTCTTGTGCCTGGTCGGCATAGTTCTACGTGCTGGTACTCCACGTCGACTAGACCCCACCTATGTGTTCATCTTGTATATTATTAGCGGTTTAAAAGG",
    "ATTCAATTTCAGTTGCCGCACGGTGTCGCATGTTGCCGCACTCTGGAATGGAGTTTAAAAATACTTTCTCCCCGGCAGATAACAGTTGGCAGTAAGCACTCTCCCAATTGGCTGCGACAAAGAGGTTCGGCTGCAGTCCAAAAATACGAGACAAAAGCAT",
    "CCGGACTGTACTATTCATGCCGACGAACATTTATCCGGACGGAGACTTAACGCATACCCCCGATAAAACCACGGTTTTCGTGTTATGGCGAGTGAGGTAGGTCTGTAGACTTGTGTAGGCATTGAGCAAATTCTCCTCGAGCGGTTAAAGTTTCAAAGTA",
    "CCCTCATGGCTACGCTTGTCAGCATAGGGACCATGGCCCTCGTGGAAAGCGTCCACGCTAAAGCGCCCTGCAAGTTCGAGCGGCTATTCAGTGTCGGGCAGTCGGAATAAGACTAATTGTACGGTGCCTGAAGGACCACCGCGGAAGTGCGTTATCGCAT",
    "GGTATTCCCCTTGGTTCTAACTATACTCCTGGCTACCTACCTCGTAAAAGACTCAGCAGCCTAACACCCGATGAATTACCCTGTCAGCTAATGAGACAGAACGGAATGTCTGGACGGTACAGGCTGGGCTCAGCTAATAATTTGGAGGGGCATGACTAAC",
    "ATTAGTAGGCGTCGTAGAGGAAAGATCTATTAGGACCCTCGACCACCTTCATTCTTGGGAGGAGGATGGGACGGGGGTAACAGTACAGGTGGTCATGCGTCGCGGCTTTTGCCTAGATTGTATAATGTGTGCGCTCTCGACCTGTACAGGCGCCCCCGTT",
    "CGATGCAGCCCCCATATAATCCTTAGAGAGCGCGGCGCTGGCACTCAAACCTCTTTATTATGACTACAATCTTTCGGTACCGAACCCTTTCGGCTTCGGCCTGGAGCGTTGGGGCACGTGCACCCTAAACAACCATGCCCCCCGATATTCTAGCTGATTC",
    "CATATGCCCTCTCATATGTAGTTACTAACGAGTGAAGATGTTGAGACTTCTGCGACTGTTAACACATTCGGTGTCGAAAGATCTTTAGGATACCCAGGGCAAGACTACGGTTAAATATATCCGGGATGTCCTCTGCCGACCTTAACAAAGCGGGTAATAT",
    "TTCTCTTACAACCACGGGAATTGCGTTGCTGCACTAGAACACCCGTAACGTGCATGAAGTCTTGCCTTTCGTAGAGAAAGATCCTATACTGCCGCATGAGGCAAAATCTAATCGTAGGAAAAGGGCAGCAAAGGATTATCTATCAGCGATCACCCCAGAG",
    "AGACCATCCCTTAGCTCCGGTTGACGTACTACTTAGTGGCGACGCATAGAAGCGACTGAAGTCAGCCGCGCGAAGGGCCAGGGCTAATCCAATACCGCGTAGGAATATCACCTTTATATTCAAAGGCTCTACACAAGGCTAATCACAGTTGGTGTATGAA",
    "GGCCATTGCCGACCTATAATCCGCCAAGTGTCTGTTAACTGGGCAAAAGGGAAGAGCAACACGGGGAACCTGTGAATGCCCAATTTTAAGATCACGAAATCTCCGGGATGTTACATTTACTCCACGGAAGACCGGGACGATGTCTAGCGAATCTACGGGC",
    "GATACCCGAGAGCAGCACCATAAGCCGGCTTGACATCGAATCTTTGCAGTTAAGACGAGCTTTATGGCATCCGACTGGCAACTAACATTCTTCAAGGCCTTTAAGGGACGTGAATGGCAACTCGAACCTCATCCACGCGACTACTGTGTAGCTACTTTAG",
    "TAGGGTAAAACATACTTCTGCGCGCGGGCCCCAACGCTGACTTTATGTTGGCCGGCGGAATCTTACCTGGATTACGTGATCCACAACAATAGAACGTGGTTCGAGTCGATAGCTACACTTCTTTTTAGGCTTCAAGTTGGACACCGATGGTGTAAGCAAT",
    "AGGGCTTTATGTATACATTTTAAGGCTTACCCGGACCCATGGGCATCAGGTTCCCAGACTGAAGCCCAGTATATTTGTACAACCAATATACTTAGCAATCCGCTGAAATGCTGGTTATTACGACGCGTCCAATCTTGGAAAATACGAGCGCGGCCCTTGG",
    "ACCGTCAGTGAGTCTTATAAAGAGTATAATTAAGAATTCTATAATTTCGTAAAGGAACTCCGATGATAACTAATCTTAGAACCCAGCCATAGATGCAATATTGCTAATCGCACGAAGACTCCCATGGCCTGTGGGTTCAGTGAGATAGGGATATAGCTAT",
    "CTGCCCTCAGCACCGCGAGAGTTGCTTAACTTGAGGATCAGGAACCATACGTCGGAGCGCTTCTATCCAAAGGCAGTTTTGCCCGAGTGGTTGAACCCTGACGGTGACCTCCAACCTCGAGTGGATACACCATGCGTTTAGACGTAGCCTGTCGTCCCGT"
};
   /* "TCACCTTCGTAGAGCCCTCCAGCCGTACAGTGCTTACTAGATAGTACATTGGCAACATCGATCAGTGTTCTCTATGCCGA",
    "TCAGGCCGGAATCAGTGACCTGATAAAAGGTCGCTCCATGGACTCCTAAAACGACGTCACGTAGAGTATAGATGACGTAC",
    "AACGGCTATTGTCCCGTACTAAGACTGGGGATGGCTCTGGGATTTATATGACCCTACGAAAACGGTAGACAGCTATCGAA",
    "CAAGCTTCTGTAAAATCACTCGGTAATGTAAAAGGTCGCGCGTCGGATGTTATAAGTAGACCTGCTAGATAAACTAAGTT",
    "ATAGCACTTCTACTCCTGAGTGTAAACCTCCAATGGTTTTATATCCCGTGCGTGAGTAAAACCAGCCAACAGTGGAGAAC",
    "CTTCTTTCTAACGGCAACACCGTTGGCGGATACCAGTGGTAACTGGTTTGACTGCTACCAGAGTTGTTATAAACTTCCTA",
    "GCATGGCTGACCTCCCTTCTCAGAGGAAGTCTCTCTACCACCAAGTGGCTGTCATGTGAAGATGCAAATCTAGTAGAACT",
    "AGAAAAAATGTAGTGACGTGCCTTATGTAACCTTATGGGGCTGAATCCAGTTTGGCTACCAATGCGGAAAGTTTAGAGCC",
    "CGCGCGGAACGCTGGGCAGACGGGAGGCCTAGTGTTCTCCGTTGCCGGTTAAGGTAACCTTTCCCTAGATACGCGCTGAG",
    "AGAAGGATCGAACGCAATCTCACCGGAACCGCATATACGTGACGGCTGCGAGCTAACGCATTCGCCTTGACGGAGTTGGC",
    "ACTGAGTACAAGAATGCTGTTATGCGTGTGTCGCAGGCCGGATTTTGAACCGAAGCGAAGGTGGAAGCTTGCTCCTCGTA",
    "TCTCCGCCCAAGGGACATCCGTATAGCAGGTGGTAGCGTCGTAACGACTCATAACGGCTTAGCGAAACAAAGTAGTGAAC",
    "TGTGTCTCTCCATTGGATCGAGCAACGTTCTGCAGTTTACCTCCGTACGCTATACCGTCGTGCAAGTGACGATACATTAC",
    "GGTACTTAGACTTGCGACTGCCGGCGGCTAATTTGCTCGGCGTAGTATGGTGCAAGTAGAGACGCCTATTCGTTCGGTAA",
    "CTATGCTTCTACCGCTCCATAATCTCTTCATAATTCACACGCGGTAACCCGGGTAGGATAAGATATGCCACCGAGACGGT",
    "TATGACGTAGCATGCCGACTGAGAGAGCTAGTGTCGGTGATACTCCACCTTCCGTCGGGTTGTGCTGAGTTACGTAAAGG",
    "GGGGGGACCTGGCCGGGGCCGAACACAGCTACTTACATAACACCGTTTTCATGCCCATACGACAGTAAGGAAAAGGCGTT",
    "ATCGTGCTAGACGTTCCGTGTATAAGTATTAAGTACCGTTACGGGGTCCCATTTTCTTGTTTGTATTACAAGTGACAACA",
    "TAAATGTCTGGATAGAGCTGAACACAAGACCCCGGGCGGGATCCGAGAGGAAATATGGATTAGCAGGAGTTGTGGGTGTG",
    "TGAATCCATGGTGGGAGATCATTCTCAAATATGATTCCCGGTAGGGACTTAAGATCACACGGATCAAACTGACCTACCCC",
    "CCCAAGCAAGATACAAAAATTTTCAATGTCGTGTCCTTACCTGTATCCAAGGGTAAGGGCGCAATGCGTCCTGCTCCGTC",
    "CCCCGAATCATTGATAGCGGGACGGGGGACACGGCAACAATGTCTATTGCCTCGGCTCACAGGGGCACTTGCATCCAGTA",
    "GCAACGACCGCAAAGAATGCGTTACTACAAGGCCGCCAAGGCTAGGAGTCAAATATAAGCCGTGACCACATCATTCGATG",
    "CCATTACTCTCACCCGTTATCTGACTCTTGCTTGGATGCCACATAGCCTACTTTCCGGTGCGCTTGAATATTCGGGGACC",
    "GGCCGATGGAAGACCTCTAAGCAGTCGGGTATCTGTTAACTAGGTTCAAGTGCGCAATCTTGATTAACTCGCTTAAAAAT",
    "GATGGTCCAGGTGTACGATTCGCCGAACCTGCGTTTCTGGAGAAACTCATCTAAAAAGATTTCACCGTAAGGGCTCGTGT",
    "TGTTGAGACCAAATCCAGTCCGAAGTAACTATAAATACTCATCGTATTTGTACTTAGACAGATCTCCAGATCGCGGTCCT",
    "GTCACCTGGCGGGACCGTTATTTAGATGACGGTAGGATCTCGAGCAGGGAGGACCTCTGAGCAGGAGGGCATGGAGCGTA",
    "AAGAAGTTTGAGAGAAGTTAGCGCCCATCCTTGACACCAACCGATAGCCCGTTCACACATCCCCTCAAGGTCTCTGTAGC",
    "GTAGGTCCGAGCTTAATCTAAACCTATGCTTACGGGCAGGGGCTGGATCAGTGCTACCTTTTCGCTCAATAGAGTCAAAT",
    "CTCCAAGTGGGGGTTGGGCATTGACGGTAGACAAGATAGTTCTAAATCCGCCAGCGCGCCTTACATGCACCAAACAACAG",
    "CTGTCTTATGAGTAATGGTTCCCCAGGCTAGCAGGGCCCGGAAAAGAGATCGGGACGCATGCAGAATTTGCCCGATCCGT",
    "GTTAGGCTGTTCCTGGACTTGTGGAGTGATGCGAGATGCCATACAATCCCTATTAAGCCGAGACGATGCTACAAGCAACA",
    "GCGCCGTCGGACGATCGTAAATTAGATCACACGTTCTATCCGTTTAACGGTAATATTAGTTTGGCCAGCAACAGTCACGG",
    "ATCGCGATGGGCCTGGTCGCCTAGTAGGTCCTGCACCTCTAAGACTACGGATGTTACCCTGGTCGTACGCGATCGCCCTT",
    "GCTCTGTGGAACAAAATTCCGTTAACACAAAGAGTGGCGTGCTAACGAGATAGTACGTAATTTGAGAGGGGACCGTAACG",
    "TGGGCTCGCTACCGTTTATGACGACCCGTCTATGCACCCGGGCTATTTGTGCGGGCTGATGGATGAATGGCAACACATTG",
    "GACGATCTTCTGCTTAGTAATCAGACTGAAGCCACGTTCTGCCTAGCTGACTTCAACGGGTAGAACCCATTGATGGTCAG",
    "GGAGCTAAAAGTGCTAATACTATGTTATGGATTGGTTGTGACGGCGAAACCTGGAAGAATGGCGTGGACAATTTCAGTAA",
    "GATAGGAAATTAGGTGTTTTCGTGAATCGAGTTCGTTGATAGGTGCATGATACAGTACACCTTCCTCTACCCGCGACAAA",
    "AGCAGGCTTTTGTACCCCAAAGTCCATTTTGCCGATACCAGCGAAGGTTGGCTAAGTAACACGGAGGTTCATTTCGTAAG",
    "TGTGCCTCGCCTTGCCTTTACAGATGTAGAATCACCAGAGAAGTTCATGCATGAAAATCTTTGGTTCGACGGTGCTCCTT",
    "ACAGCTCAGCTGGCTGATCTAGCGAGCACCATAGTTCCAGGTTCGGAGAGTTGCCTGAGATAGATGCAGCTTGATGTTCG",
    "AGGCATATGGATACCAGCTCAGCTGTGAGCTAGTTTCGATATCAATTGTCCCGACACTCCTTGGATGGTTGTGAACAATG",
    "CTAAAGAGAGTGCCGGAGTTCCATCGCATATCAAGGCTAGTGAAACAGTCAAGGAAATCGGGCAGACAATGTTAGTCTGG",
    "ATAAGATAGTCATACTACGGCCCGTGAGAGATTGCTGGATAAGTACCCGGCGTAGTAAAGGTCCACCTGCCACTCCTTAT",
    "GACGGCCTAGTGATGAAGACATTTTGTTGCGCATTGGAACCTTAAACGTCGTATCAAAATGGGGAAGTTGGGCAGAAAAG",
    "ACTGCGGGGCACAGGAAGGAGGTTCCGAATTAGGATTGCTCTACGGATTTAATAGGCCACAATCCTCACTCGTAGGGGAA",
    "ATTTGTCGGGTCGCGACAAGTTCTATCCGAAGAGGAGGTTTACAGGAGGAAAAAACTTTTATGCGGAGCAAAACCGGGGT",
    "CCACTGAGTAATTATTAGACCTTTTCTTGCATCTCGAATCGCTAATCCATTAGGGTATCTCTATCCGAGGCGCCTCGCAG",
    "ACCAGGAGACTAAGATATATTCATGATGCAAACAACAATCACCAACGCAGGGTTCAGAACTGCTGACATGGACTGCTTGC",
    "CACCAATCTGGGCTAATCAACAGAATTGGGATATTCTTATCGACTTTGGCATTCAAACAGGCTGCAAGATGATGTTCTAA",
    "GGAAAGGGTCCTCTTACAGAGGGGGAAGTACACCGGGCACCTCTCATTATAACCACCACGAGACAGGCTCTCGGGGCAAC",
    "CTTTTCCGCAAAATAAGGAGCTCTACGAGGCCCAGCAGAGCATCCGTGGCACTCATCGGGGCATAATTCCGGGTACATCG",
    "TCGATTTGTGGGTACGTAGGAACGCCGAACGTGAGTAACCCTCTAAGCGATTCAATATAACAGAGGGCTGTAAGTTACTG",
    "TAAATGGCTATGTTAATCTCCGAAAGTGTGGGCGAATGAAAGTTTGTATGCGCCATCTAATACACCAGAAGTATGACAAC",
    "ACGCGAAGGTCGTCCGCCCGTAGCTCGTGCTGTGCAGGGCAAGACTTCCTTTTTCATCCCTGTCGGGGTGCCCAGTTCGG",
    "ACCCTCCACTAGTAGATAGGTACCCCCGGTTCATGGTGACGTAACCCGTGTGCGATTGTAGCTTGACAAATGGGCCGAAC",
    "ACCCGTGACCCCAAGCACGGGTCATACGTCACCTTGGAATAGAGCACGTCCTAGCAACCAGTAGGACACGAATGCGGAGT",
    "TAATTCACCGCAGCAGCATTCTTCATCCAGAGCGTGGAACCCGGACTGTTGGACGGATACACGTAAACGCCTTGGTGACG",
    "CTTTAGTGCGATCGCTAGCTAACCTGGGCCTCCGGGGCCGTGCAAACTTAGGGATCGCCAAAAACGCGCAGTATCCACAG",
    "GTCATTATTTTAAACGGGCGGGGACTTTTTATAGTTACTTAAATACTCCAGCAAATTGTATTTGCATAGCGAGTATATCG",
    "CAGTTTCGTTGATAGGGATCCTTCGCGCAGTTAAGGCCTCTGCGCGCACGACTATTCTTTAGATAAGTACGTTCTAGGTA",
    "GGGTCTTTACCCGAATTCGTGCCCGTTGCCAGAATTCTCATTGCCCAATCAGAGTTGTCGGTGGTTGAAGGATTTGATCG",
    "TCGGTGTGCGGTGCTTCGGTCGTTTGAGGAGCAATCCTGAGCGGATTTTCACGATTCGACCGCACAAGATAGTTAGGTAA",
    "ATCTGGCTCACGGCGAGGGAGCAATAAAAACGCCGTATACTAGTGGGGATCACAGATAGTCGGTAAGAACGACATTGGGC",
    "AGGGGTCGCACCGATTCTTAATCTTCATGAAGCAGATGATAACTACAAGATCCCGGTGAGGATACTTTTGAGACGAGCGC",
    "CGATTAAATCGCCCGGCTTCTCACCTATACCCAATTACCGTCGTTCGCGCTAGAGCCGTTAGTGAGTGAACGGTATTTAA",
    "ATGGAAGTATCTGACACGTGCAAACGGATCAAACGGTACAACTCTTGGGCGGGATGCCGCTAATGAAGACTGGCGAACTA",
    "ACGTTAACAACACGTTAGTGGCGTAAGTCCTTCAGTCGCTTGGTACCAAAGACACCACATCAAAACTGCTTCGAGGTTCC",
    "TCGTAGTCTGGGGACCGCACGTCATGGTGTTTCGGGAGGGAGTGGCGAGGCATTCTACCCCATAGCCGGCGTTGGGATAA",
    "GTAAAGACTAAAGGCGATTGCTGCCGATTCCCAATCTATTTAAGTCCTATAAGTAGGTCGTCATGGACACGAACGTGGGC",
    "AGTTCACTCGCTGGTCATGGACGGTCCGTCATCTTGTTCCCCCCTTTCCCGCTATTTGAGTATATCCACAAACAGCCCGA",
    "CAACCTAAATCATCGCCTACTTGCTTACACGCTAACGGTACACTATCGACCTATAAGAGGCCGGTCGACAGCTGTTCGGC",
    "TTTCCTCGGACAACTTACGTCCTGGTAGGCACAGCCACAATAGCTTAAATGATACTGCCAGGCCGACCGTGTCTTCGCGA",
    "ACGCGAGAGCCTATTCATCATCGAAGGGTTAAGGTATAAGGGCCCCAAGTTTACCCCAGATGGGAGTGGCCCAAATTAAC",
    "ACAGCGTTCGCACACCGAAGTGTGCCCTAGGTGCTCAACAGAGCCCCACTATGGTCAAACTCAAACGGGGAAGGCTATAA",
    "TTTTGGTCCGCGCACTACAGTTATTTGCTCATAGGTACTGATGGGCGACGCACCATATGCGTTACTTATGATACTCGATG",
    "GCATGGAGTCATTGTCTATGATAAGATCATACTAGTCTATAGATGCGGATGTTTCCTAGGACTGGATGCTTTCAATTGCT",
    "ATATGGTCTATGTTCCTGTGATTGGGGTTACTGACCATATGCGTCCGGGCCAAGCAGAGACTGGGCTCACTGCCTTGCAG",
    "GCTCTTGGGTTAATAAGCACGCTGTTCGTTGGGTGAATCTGTCCTCTACCATTTGCTATCGAGATAAGAGCGGCGAAATG",
    "TAACGGGAAATATAATTGTTGTCGAATTAAACGAAAGATCTGAGGTACATCTAGGACGCCTCGACGCGTTCACCGATCAG",
    "GATGCAACTCCCAGGCAAGAGGCGATGATCCGTGTATTTTAATCTGATGATCTAAATTTGTTGCCGTCAACGATGAGGCA",
    "TATACATTAGTCAAAGAAATGCAGGCTTAACTATTTGAGTGGATGGAAGCGGAGCACGTTCCCCCTTGCTCGAGGATTGC",
    "TGCAGTGATGGGGACAGTCCGTTAGTGCAAGTCGCGGCGAGTGGCAGAAGGAGATGTCAACAGTGCCAGAAGTAGCTACA",
    "GGTGCGGATTTTAACATGGGATGCCTGTTGGTTTATTGTGGATATTTGGTCTATGAAAATGGACGGGCTTTTAGCGAAAC",
    "GTGGACTCTTAGGCGTGTACTATCATTGCTTGTCATCCGTTAGGGCGTCGTACGCCGTCGTTAAGTGCGGACGCATAAAG",
    "TTATGATTCCAATATAGTCAGACTTAAGGCCGCGGCAAAGCCTACTGCGCTCCGTCCAACAGCTATTCAATACACCGTTG",
    "AAAGAAAGCCCACTATGTGGAAATTCGTACATCAAGGCGGAATTCCCTTGTAACTGAACCCGCTACCTCTACGTTCAGGG",
    "TGTAACCGCAGGTCCCTCACAAGGGGTGCCACATACCAACAATAATAAATCATCTGTACCGAGTGTTTCCCGATGGATAT",
    "CTGGCCAGTTGTAGGGCAAGGGATATAGTAGCCAGTTGGGACTGACGGGCATTTTAAGTCGTGAACGATTCTAAATCATG",
    "AGAAGCAGTTTCGGATAGTAGTGTGGCGTTTTCTAACATCTAAAGACCCCTGTGTTCTTAATAACGCATAGCGATGGGTG",
    "ATTAGTATTTACTGACGCAAGTTATGGTGCCCCAAGTTGCATAAGCTAAAGCCTGCATACTTGGCAGGTCGGGTGCTAAG",
    "CCCTTAGACTGGGGGAGAGAGCCAATCTTGAAAATGGTAGAGTAGGGTCTAAGAGGACGAAGCAAGATCGTGATTCGGGT",
    "CATTATGTAACGCCCAGGCGCACGGCTCGTGCAGTGGTAAGCCGCGGCCCAAAAACAGCGGAAGCGAACCAAACTGCTCT",
    "CCGGAAAATACACCTTTCAAACGTCTGCCGGCTTCCATACTCATGTCCGAGAAACCCGTGCGGTTAATCCTTGCGAGAAG",
    "CTTGACAGGCTCACGGAGTATGGCCGAGTCTCTCGATAACGTGATTCCGCGAGTCTTAACAGCCGAACGATCGTAGGTAT",
    "TAATCTTCACAAGCGTCACGATTTTCCATCAGAAAGCAGAGCACGCTGGGACCTTGGTAATGTGGCCAGATCCCGCACCC"
}; */