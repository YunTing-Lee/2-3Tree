#include <iostream>
#include <fstream>
#include <vector>
#include <string>
# include <cstdlib>

using namespace std;

struct SchoolType{
    int no ; // �Ǹ�
    string schoolId ;  // �ǮեN�X
    string schoolName ;  // �ǮզW��
    string departmentId ; // ��t�N�X
    string departmentName ; // ��t�W��
    string dayNight ; // �鶡�A�i�קO
    string level ;  // ���ŧO
    int studentNum ; // �ǥͼ�
    int teacherNum ; // �Юv��
    int graduateNum ; // �W�Ǧ~�ײ��~�ͼ�
    string city ; // �����W��
    string system ; // ��t�O
}; // struct SchoolType

struct SchoolName{
  int no ;
  string schoolName ;  // �ǮզW��
};

struct Department{
  int no ; // �Ǹ�
  string departmentName ; // ��t�W��
};

class TwoThreeNode{
public :
  vector<vector<SchoolName> > schoolsKey ; // �C�Ӹ`�I�̦h�s���key
  TwoThreeNode * parent ;   // ���˸`�I
  TwoThreeNode * leftChild ; // ����`�I
  TwoThreeNode * midChild ;  // �����`�I
  TwoThreeNode * rightChild ; // �k��`�I

  TwoThreeNode(){
    parent = NULL ;
    leftChild = NULL ;
    midChild = NULL ;
    rightChild = NULL ;
  } // constructor

   TwoThreeNode( vector<SchoolName> aSchool ) { // �]aSchool���s�`�I���x�s�����
    parent = NULL ;
    leftChild = NULL ;
    midChild = NULL ;
    rightChild = NULL ;
    schoolsKey.push_back(aSchool) ;
   } // constructor

}; // class TwoThreeNode


class TwoThreeTree{
  public :
      TwoThreeNode * root ;  // �ڵ��I

      void twoThreeInsert( SchoolName aSchool, TwoThreeNode * &temp ) ; // ���J�s���
      void sortThreeKey( vector<vector<SchoolName> > & tempKey );  // �N�T�����key���Ƨ�
      int getHeight( TwoThreeNode * temp );  // ���o�`�Itemp������
      void split( vector<SchoolName> newKey , TwoThreeNode * splitNode, TwoThreeNode * leftLeft,TwoThreeNode * leftRight,
                  TwoThreeNode * rightLeft, TwoThreeNode * rightRight ) ;
      // newKey�O�n�s�W��splitNode���`�I�A��splitNode�w���A�ҥH�n����splitNode�o�Ӹ`�I�A
      //�Y�b�o���������e�A�w�g��splitNode���l�`�I�����L�A���᭱4�ӰѼƬ��l�`�I�����᪺���СA�Y���e�S�����L�A�h�ǤJNULL
      void traversal( TwoThreeNode * temp );
      void printRoot( vector<SchoolType> sch);  // �L�X�ڸ`�I�����
      vector<int> searchCollege( string collegeName  ) ;
      int numOfNode( TwoThreeNode * temp ) ;
      int sizeOfTree( TwoThreeNode * walk );
      int numOfKey( TwoThreeNode * walk) ;

  TwoThreeTree(){
    root = NULL ;
  } // constructor
};


int ReadCommand() ;  // ŪCommand�A�Y�O0�N��������
int reCommand() ;
void ReadCollegeAndDepartment( string & collegeName, string & departmentName ) ;
void Enter() ;      // Ū��'\n'����
bool ReadFile( vector<SchoolType> & sch, string & fileId ) ;
void ReadInputFileName( string & fileId,string & inputFullName ) ; // Ū�ɮ׽s��
bool OpenInputFile( string & fileId,string & inputFullName,fstream & inputFile ) ; // ���}�ɮ�
void ReadInputData( fstream & file, vector<SchoolType> & sch ) ; // Ū�ɮ׸��
string ReadString(fstream & file) ; // Ūfile�̪��@�Ӧr��
int StringToInt( string str ) ; // �N�r���ন�Ʀr
bool IsDigit( char ch ); // �P�_ch�O�_���Ʀr
int getMax( int a, int b, int c ) ;

int Max( int a, int b ) {
  if ( a > b )
    return a ;
  else
    return b ;
} // int Max()


 int TwoThreeTree :: numOfKey( TwoThreeNode * walk) {
    if ( walk == NULL )
        return 0 ;
    else if( walk->schoolsKey.size() == 1 )
        return 1 +  numOfKey(walk->leftChild) +  numOfKey(walk->rightChild) ;
    else
        return 2 +  numOfKey(walk->leftChild) +  numOfKey(walk->midChild) + numOfKey(walk->rightChild) ;
 }

int main(){

    int command = ReadCommand() ;


    fstream inputFile ;
    string inputFullName, fileId ;
    vector<SchoolType> sch ;
    TwoThreeTree gTwoThree ;
    bool firstDone = false, secondDone = false, thirdDone = false ;

    while ( command != 0 ) {
        switch(command){
            case 0 : break ;
            case 1 : {

                sch.clear() ; // �M�Ÿ��
                secondDone = false ;
                thirdDone = false ;

                while ( ! ReadFile(sch, fileId) ) { // �YŪ�쪺fileId��"0"�A�h�|�^��false�A�A���sŪcommand
                    if ( reCommand() == 0 ) // ���sŪcommand
                    return 0 ; // command��0�A�h��������
                } // while

                TwoThreeTree twoThree ;

                for ( int i = 0 ; i < sch.size() ; i++ ) { // �@�Ӥ@�ӷs�W��23��
                    SchoolName aSchool ;
                    aSchool.no = sch[i].no ;
                    aSchool.schoolName = sch[i].schoolName ;
                    twoThree.twoThreeInsert( aSchool, twoThree.root ) ;
                } // for

                gTwoThree = twoThree ;
                cout << "Tree Height =  " << twoThree.getHeight( twoThree.root )  << endl ;
                twoThree.printRoot(sch) ;

                int numOf23Node = twoThree.numOfNode(twoThree.root) ;
                int numOf23School = twoThree.numOfKey( twoThree.root ) ;
                cout << "Num of 23Node = " << numOf23Node << endl ;
                cout << "NUm of 23School = " << numOf23School << endl ;
                cout << "SIZE Of 23Tree = " << twoThree.sizeOfTree(twoThree.root) << "bytes. " << endl ;

                break ;
                firstDone = true ;
      } // case1
    default :
      cout << "### command does not exist  ###" << endl ;
    } // switch command
     command = ReadCommand() ;
  } // while(command != 0)

    return 0;
} // main()

int ReadCommand(){  // Ūcommand
  cout << "*******  Search Tree Utilities   ******" << endl ;
  cout << "* 0. QUIT                           ***" << endl ;
  cout << "* 1. Build 2-3 tree                 ***" << endl ;
  cout << "***************************************" << endl ;
  cout << "Input a choice(0,1) : "  ;
  string command ;
  cin >> command ;
  int num = atoi( command.c_str() );
  char ch ;
  cin.get(ch);
  if ( ch != '\n')
    Enter() ;
  return num ;
} // ReadCommand


int reCommand(){
  int command = ReadCommand() ;
  if ( command == 0 )
    return 0 ;
  else if ( command == 1 )
    return 1 ;
  else {
    cout << "### command does not exist  ###" << endl ;
    return reCommand() ;
  } // else if

} // reCommand()



void Enter(){        // Ū��'\n'����
  char enter ;
  cin.get(enter) ;
  while( enter != '\n' )
    cin.get(enter) ;
} // Enter()

bool ReadFile( vector<SchoolType> & sch, string & fileId ){
  fstream inputFile ;
  string inputFullName ;
  ReadInputFileName( fileId,inputFullName ) ;   // Ū�ɮ׽s��
  if ( ! OpenInputFile( fileId, inputFullName, inputFile ) )  // �}���ɮסA�Y�ɮ׽s���O0�h�����������sŪcommand
    return false ;
  else {
    ReadInputData(inputFile,sch) ;
    inputFile.close();
    return true ;
  } // else
} //  ReadFile()

void ReadInputFileName( string & fileId,string & inputFullName ){
  cout << "Input a filename(eg.input1, input2......)[0]Quit : " ;
  cin >> fileId ;
  char ch ;
  cin.get(ch);
  if ( ch != '\n')
    Enter() ;
  //inputFullName = "input.txt" ;
  inputFullName = fileId + ".txt";
} // ReadInputFileName

bool OpenInputFile( string & fileId,string & inputFullName,fstream & inputFile ){
  if ( fileId.compare("0") == 0 )  // �p�G�s���O0�A���������A���sŪcommand
   return false ;
  else {
    inputFile.open( inputFullName.c_str(), ios::in ) ;
    while ( ! inputFile ) {    // �����ɮצ��\�}��
      cout << "### " << inputFullName << " does not exist ### " << endl ;
      fileId = "" ;
      ReadInputFileName( fileId,inputFullName ) ;
      if ( fileId.compare("0") == 0 )   // �p�G�s���O0�A���������A���sŪcommand
        return false ;
      inputFile.open( inputFullName.c_str(), ios::in) ;
    } // while
  } // else
  return true ;
} // OpenInputFile()

void ReadInputData( fstream & file, vector<SchoolType> & sch ){
  string line ;
  for ( int i = 0 ; i < 3 ; i++ ) // Ū���e3�C
    getline(file,line) ;
  SchoolType aSchool ;

  while( ! file.eof() ) {
    aSchool.no = sch.size()+1 ;
    aSchool.schoolId = ReadString(file);
    aSchool.schoolName  = ReadString(file);
    aSchool.departmentId  = ReadString(file);
    aSchool.departmentName  = ReadString(file);
    aSchool.dayNight  = ReadString(file);
    aSchool.level  = ReadString(file);
    aSchool.studentNum  = StringToInt(ReadString(file)) ;
    aSchool.teacherNum  = StringToInt(ReadString(file)) ;
    aSchool.graduateNum  = StringToInt(ReadString(file)) ;
    aSchool.city  = ReadString(file);
    aSchool.system  = ReadString(file);
    sch.push_back(aSchool) ;
  } // while

  if ( aSchool.schoolId =="" && aSchool.schoolName == "" && aSchool.departmentId == "")
    sch.pop_back();
} // ReadInputData()

string ReadString(fstream & file){
  string str = "" ;
  char aChar = file.get();
  while( aChar != '\t' && aChar != '\n' && aChar != EOF  ) {
    str = str + aChar ;
    aChar = file.get();
  }
  return str ;

} //ReadString(fstream & file)

void ReadCollegeAndDepartment( string & collegeName, string & departmentName ){
  char ch ;
  cout << " Enter a college name to serach : [*] "  ;
  cin >> collegeName ;
  cin.get(ch);
  if ( ch != '\n')
    Enter() ;
  cout << " Enter a department name to serach : [*] " ;
  cin >> departmentName ;
  cin.get(ch);
  if ( ch != '\n')
    Enter() ;
} //  ReadCollegeAndDepartment()



int StringToInt( string str ){  // ��string����int
  int sum = 0 ;
  for ( int i = 0 ; i < str.length() ; i++ ) {
    if ( IsDigit( str[i]) ) {
      int num = str[i] - '0' ;
      sum = sum*10 + num ;
    } // if
  } // for

  return sum ;
} // StringToInt()

bool IsDigit( char ch ) { // �O���O�Ʀr
  if ( ch >= '0' && ch <= '9')
    return true ;
  else
    return false ;
} // IsDigit()


void TwoThreeTree :: twoThreeInsert( SchoolName aSchool, TwoThreeNode * & twoThreeNode ) { // �s�WaSchool��23��

  TwoThreeNode * temp = twoThreeNode ;
  vector<SchoolName> newKey ;
  newKey.push_back( aSchool ) ;

  if ( twoThreeNode == NULL ) {
      twoThreeNode = new TwoThreeNode(newKey) ; // �s�W�@�Ӹ`�I
  } // if
  else if ( temp ->schoolsKey.size() == 1 ) {  // key�u���@��
    if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) == 0 ){ // aSchool���ǮզW�ٻPtemp�ҫ��V�`�I�����@����ȬۦP
        temp->schoolsKey[0].push_back(aSchool) ;                                // �NaShool�s�W�ܳo����Ȫ��̧���
    } // if �@�˦W�r
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) < 0 ) { // aSchool���ǮզW�٤p��temp�ҫ��V�`�I�����@�����
       if( temp->leftChild == NULL ) { // temp�w�g���츭�`�I�F
          temp->schoolsKey.insert(temp->schoolsKey.begin(), newKey ) ; // �N��aSchool�إߪ����newKey���J�btemp����Ȫ��̫e��
       } // if
       else {
         twoThreeInsert(aSchool, temp->leftChild ) ; // �٨S���츭�`�I�A�~�򩹤U��
       } // else
    } // else if
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) > 0 ) { // aSchool���ǮզW�٤j��temp�ҫ��V�`�I�����@�����
       if( temp->rightChild == NULL ) { // temp�w�g���츭�`�I�F
          temp->schoolsKey.push_back(newKey) ; // �N��aSchool�إߪ����newKey�s�W�btemp����Ȫ��̧���
       } // if
       else {
         twoThreeInsert(aSchool, temp->rightChild ) ; // �٨S���츭�`�I�A�~�򩹤U��
       } // else
    } // else if

  } // else if key ���@��
  else if ( temp ->schoolsKey.size() == 2 ) { // ����2��key���`�I
    if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) == 0 ){
        temp->schoolsKey[0].push_back(aSchool) ;
    } // if �@�˦W�r
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[1][0].schoolName) == 0 ) {
        temp->schoolsKey[1].push_back(aSchool) ;
    } // else if
    else if ((aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) < 0 ) {
       if( temp->leftChild == NULL ) { // �w�g���츭�`�I�F
          split( newKey, temp, NULL, NULL, NULL,NULL) ;
          // ����
       } // if
       else {
        twoThreeInsert(aSchool, temp->leftChild ) ;
       } // else
    } // else if
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) > 0 && (aSchool.schoolName).compare(temp->schoolsKey[1][0].schoolName) < 0) {
       if( temp->midChild == NULL ) { // �w�g���츭�`�I�F
          split(newKey,temp, NULL, NULL, NULL,NULL) ;
       } // if
       else {
        twoThreeInsert(aSchool, temp->midChild ) ;
       } // else
    } // else if
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[1][0].schoolName) > 0 ) {
       if( temp->rightChild == NULL ) { // �w�g���츭�`�I�F
          split(newKey,temp, NULL, NULL, NULL,NULL) ;
       } // if
       else {
        twoThreeInsert(aSchool, temp->rightChild ) ;
       } // else
    } // else if
  } // else two keys
} // twoThreeInsert()

void TwoThreeTree :: split( vector<SchoolName> newKey , TwoThreeNode * splitNode, TwoThreeNode * leftLeft,TwoThreeNode * leftRight,
                           TwoThreeNode * rightLeft, TwoThreeNode * rightRight ) {

  vector<vector<SchoolName> > tempKeys ; // �Τ@�ӼȮɪ�vector�s�i3��key�A���L�̥Ѥp��j�Ƨ�
  tempKeys.push_back(splitNode->schoolsKey[0]) ;
  tempKeys.push_back( splitNode->schoolsKey[1] ) ;
  tempKeys.push_back(newKey) ;
  sortThreeKey(tempKeys) ; // �N�T��key�Ƨ�

  // cout << "SORTED " << tempKeys[0][0].num << "  " << tempKeys[1][0].num << "  " << tempKeys[2][0].num << endl ;

  TwoThreeNode * newNode = new TwoThreeNode( tempKeys[0] ) ; // �γ̤p��key new�@�ӷs���`�I
  splitNode->schoolsKey.clear() ; // �N�쥻�n�������I���M��
  splitNode->schoolsKey.push_back( tempKeys[2]) ; // �b�s�i3��key���̤j�����@��

  //splitNode->midChild = NULL ;

  if ( leftLeft != NULL ) {  // ���O�Ĥ@�������`�I�A���⤧�e�����n���I���W

    newNode->leftChild = leftLeft ;
    leftLeft->parent = newNode ;

    newNode->rightChild = leftRight ;
    leftRight->parent = newNode ;

    splitNode->leftChild = rightLeft ;
    rightLeft->parent = splitNode ;

    splitNode->rightChild = rightRight ;
    rightRight->parent = splitNode ;

    splitNode->midChild = NULL ;

  } // if


  if ( splitNode->parent == NULL ) { // �Y�n�������`�I�S�����`�I�A��ܷ|���@�ӷs��root�A�s���������

    root = new TwoThreeNode( tempKeys[1]) ; // �Τ�����ȷs�W�@�ӷs���ڸ`�I
    root->leftChild = newNode ;       // root�����p�ĬO���new���s�`�I�A��ȳ̤p������
    newNode->parent = root ;
    root->rightChild = splitNode ;   // root���k�p�ĬO�쥻�n���������Ӹ`�I
    splitNode->parent = root ;
  } // else if
  else if ( splitNode->parent->schoolsKey.size() == 1 ) { // �n�������I�����`�I�u���@�����
    TwoThreeNode * parentOfSplit = splitNode->parent ;

    if ( ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[0][0].schoolName) < 0 ) {  // splitNode�O�@parentOfSplit��leftChild�A�O���`�I�n����
      parentOfSplit->schoolsKey.insert( parentOfSplit->schoolsKey.begin(), tempKeys[1]) ;  // �N�ƧǹL���b������key���J�b���`�I��key���Ĥ@�Ӧ�m

      // �]���e���O��̤j��key��bsplitNode�A�̤p��key��bnewKey�A��splitNode�S�O���`�I�A���`�I���ӭn��̤p�ȡA
      // �ҥH�⥪�`�I�אּnewNode�B�����`�I�אּsplitNode�A�ӥk�`�I���ΰʨ�
      parentOfSplit->leftChild = newNode ;  // ���`�I�����p�ĬOnewNode�A�̤p��key
      newNode->parent = parentOfSplit ;
      parentOfSplit->midChild =splitNode ; // ���`�I�������p�ĬOsplitNode�A�̤j��key
      splitNode->parent = parentOfSplit ;

    } // if split the leftChild
    else if ( ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[0][0].schoolName) > 0 ) { // splitNode�O�@parentOfSplit��rightChild�A�O�k�`�I�n����
      parentOfSplit->schoolsKey.push_back(tempKeys[1]) ;  // �N�ƧǹL���b������key�s�W�ܤ��`�I��key���̧���

      // �]���e���O��̤j��key��bsplitNode�A��splitNode�S�O�k�`�I�A�ҥH�N���ΦA�ʤF�A�]���ݭn�ʨ쪺�u�����`�I�������p�ġA���̤p��key
      parentOfSplit->midChild = newNode ; // ���`�I�������p�ĬOnewNode�A�̤p��key
      newNode->parent = parentOfSplit ;

    } // else if

  } // else if
  else if ( splitNode->parent->schoolsKey.size() == 2 ) { // �n�������I�����`�I�]�������ȡA��ܭn�~�����

    TwoThreeNode * parentOfSplit = splitNode->parent ;

    if (  ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[0][0].schoolName) < 0 ) { // �n�������I�OleftChild

      TwoThreeNode * LL = newNode ;
      TwoThreeNode * LR = splitNode ;
      TwoThreeNode * RL = parentOfSplit->midChild ;
      TwoThreeNode * RR = parentOfSplit->rightChild ;
      split(tempKeys[1], splitNode->parent, LL, LR, RL, RR ) ;
    } // if
    else if (  ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[1][0].schoolName) > 0 ) { // �b�̥k�䪺�I�n����
      TwoThreeNode * LL = parentOfSplit->leftChild ;
      TwoThreeNode * LR = parentOfSplit->midChild ;
      TwoThreeNode * RL = newNode ;
      TwoThreeNode * RR = splitNode ;
      split(tempKeys[1], splitNode->parent, LL, LR, RL, RR ) ;

    } // else if
    else{  // �n�������I�OmidChild
      TwoThreeNode * LL = parentOfSplit->leftChild ;
      TwoThreeNode * LR = newNode ;
      TwoThreeNode * RL = splitNode ;
      TwoThreeNode * RR = parentOfSplit->rightChild ;
      split(tempKeys[1], splitNode->parent, LL, LR, RL, RR ) ;
    } // else
  } // else if
} // split()

void TwoThreeTree :: printRoot( vector<SchoolType> sch ) {

  cout << "ROOT : " << endl ;
  int numOfRoot = 0 ;
  if ( root == NULL )
    return ;
  if ( root->schoolsKey.size() == 1 ) {
    for( int j = 0 ; j < root->schoolsKey[0].size() ; j++ ) {
        numOfRoot++ ;
        cout << numOfRoot << " : "  ;
        int rootIndex = root->schoolsKey[0][j].no - 1 ;
        cout << "[" << sch[rootIndex].no << "] " ; // �Ǹ�
        cout << sch[rootIndex].schoolName << ", " << sch[rootIndex].departmentName << ", " << sch[rootIndex].dayNight << ", "
             << sch[rootIndex].level << ", " << sch[rootIndex].studentNum << endl ;
    } // for
  } // if root has only one key
  else{ // else root has two keys
    if ( root->schoolsKey[0][0].no < root->schoolsKey[1][0].no) {

      for ( int i = 0 ; i < root->schoolsKey.size() ; i++ ) {
        for( int j = 0 ; j < root->schoolsKey[i].size() ; j++ ) {
          numOfRoot++ ;
          cout << numOfRoot << " : "  ;
          int rootIndex = root->schoolsKey[i][j].no - 1 ;
          cout << "[" << sch[rootIndex].no << "] " ; // �Ǹ�
          cout << sch[rootIndex].schoolName << ", " << sch[rootIndex].departmentName << ", " << sch[rootIndex].dayNight << ", "
               <<  sch[rootIndex].level << ", " << sch[rootIndex].studentNum << endl ;
        } // for
    } // for

    } // if
    else{
      for ( int i = 1 ; i >= 0 ; i-- ) {
        for( int j = 0 ; j < root->schoolsKey[i].size() ; j++ ) {
          numOfRoot++ ;
          cout << numOfRoot << " : "  ;
          int rootIndex = root->schoolsKey[i][j].no - 1 ;
          cout << "[" << sch[rootIndex].no << "] " ; // �Ǹ�
          cout << sch[rootIndex].schoolName << ", " << sch[rootIndex].departmentName << ", " << sch[rootIndex].dayNight << ", "
               <<  sch[rootIndex].level << ", " << sch[rootIndex].studentNum << endl ;
        } // for
      } // for
    } // else
  } // else
} // printRoot()


void TwoThreeTree :: sortThreeKey( vector<vector<SchoolName> > & schoolsKey ){
  vector<SchoolName> temp1 = schoolsKey[0] ;
  vector<SchoolName> temp2 = schoolsKey[1] ;
  if ( ( schoolsKey[2][0].schoolName).compare(schoolsKey[0][0].schoolName) < 0 ) {
    schoolsKey[0] = schoolsKey[2] ;
    schoolsKey[1] = temp1 ;
    schoolsKey[2] = temp2 ;
  } // if
  else if ( ( schoolsKey[2][0].schoolName).compare(schoolsKey[1][0].schoolName) < 0 ) {
    schoolsKey[1] = schoolsKey[2] ;
    schoolsKey[2] = temp2 ;
  } // else if
} // sortThreeKey

int TwoThreeTree :: getHeight( TwoThreeNode * temp ){

  if ( temp == NULL ) {
    return 0 ;
  } // if
  else {
    return 1 + getMax( getHeight(temp->leftChild), getHeight(temp->midChild), getHeight( temp->rightChild) ) ;
  } // else
} // getHeight()

vector<int> TwoThreeTree :: searchCollege( string collegeName ) {
  vector<int> sameNo ;
  TwoThreeNode * twoThreeWalk = root ;

  while(twoThreeWalk != NULL ) {
    if ( twoThreeWalk->schoolsKey.size() == 1 ) {
      if ( collegeName.compare(twoThreeWalk->schoolsKey[0][0].schoolName) ==  0) {
        for( int i = 0 ; i < twoThreeWalk->schoolsKey[0].size() ; i++ ) {
          sameNo.push_back( twoThreeWalk->schoolsKey[0][i].no) ;
        } // for
        return sameNo ;
      } // if
      else if ( collegeName.compare(twoThreeWalk->schoolsKey[0][0].schoolName) < 0 ) {
        twoThreeWalk = twoThreeWalk->leftChild ;
      } // if
      else {
        twoThreeWalk = twoThreeWalk->rightChild ;
      }
    } // if
    else{ // ��������
      if ( collegeName.compare(twoThreeWalk->schoolsKey[0][0].schoolName) ==  0) {
        for( int i = 0 ; i < twoThreeWalk->schoolsKey[0].size() ; i++ ) {
          sameNo.push_back( twoThreeWalk->schoolsKey[0][i].no) ;
        } // for
        return sameNo ;
      } // if
      else if ( collegeName.compare(twoThreeWalk->schoolsKey[1][0].schoolName) ==  0) {
        for( int i = 0 ; i < twoThreeWalk->schoolsKey[1].size() ; i++ ) {
          sameNo.push_back( twoThreeWalk->schoolsKey[1][i].no) ;
        } // for
        return sameNo ;
      }
      else if ( collegeName.compare(twoThreeWalk->schoolsKey[0][0].schoolName) < 0 ) {
      twoThreeWalk = twoThreeWalk->leftChild ;
      } // if
      else if (  collegeName.compare(twoThreeWalk->schoolsKey[1][0].schoolName) > 0 ){
        twoThreeWalk = twoThreeWalk->rightChild ;
      } // else if
      else{
        twoThreeWalk = twoThreeWalk->midChild ;
      } // else

    } // else
  } // while
  return sameNo ;

} // TwoThreeTree :: searchCollege()

int TwoThreeTree :: numOfNode( TwoThreeNode * temp ){
  if ( temp == NULL )
    return 0 ;
  return 1 + numOfNode( temp->leftChild ) + numOfNode(temp->midChild) + numOfNode( temp->rightChild) ;

} //TwoThreeTree :: numOfNode


int getMax( int a, int b, int c ) {
  if ( a > b && a > c )
    return a ;
  else if ( b > a && b > c)
    return b ;
  else
    return c ;
} // getMax()


int TwoThreeTree :: sizeOfTree( TwoThreeNode * walk ){
  if ( walk == NULL )
    return 0 ;
  else if ( walk->schoolsKey.size() == 1 ) {
    int sizeOfNode = 32 ; // �@��pointer�e8��byte�A1��aTwoThreeNode��4��pointer
    for( int i = 0 ; i < walk->schoolsKey[0].size() ; i++ ) {
      int sizeOfString = walk->schoolsKey[0][i].schoolName.size();
      int sizeOfNo = sizeof(walk->schoolsKey[0][i].no) ;
      sizeOfNode = sizeOfNode + sizeOfString + sizeOfNo ;
    } // for
      return sizeOfNode + sizeOfTree(walk->leftChild) + sizeOfTree(walk->rightChild) ;
  } // else if
  else{
    int sizeOfNode = 16 ; // �@��pointer�e4��byte�A1��aTwoThreeNode��4��pointer
    for( int i = 0 ; i < walk->schoolsKey.size() ; i++ ) {
        for( int j = 0 ; j < walk->schoolsKey[i].size() ; j++ ) {
          int sizeOfString = walk->schoolsKey[i][j].schoolName.size();
          int sizeOfNo = sizeof(walk->schoolsKey[i][j].no) ;
          sizeOfNode = sizeOfNode + sizeOfString + sizeOfNo ;
        } // for
    } // for
    return sizeOfNode + sizeOfTree(walk->leftChild) + sizeOfTree(walk->midChild ) + sizeOfTree(walk->rightChild) ;
  } // else

} // sizeOfTree()
