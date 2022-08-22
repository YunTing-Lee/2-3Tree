#include <iostream>
#include <fstream>
#include <vector>
#include <string>
# include <cstdlib>

using namespace std;

struct SchoolType{
    int no ; // 序號
    string schoolId ;  // 學校代碼
    string schoolName ;  // 學校名稱
    string departmentId ; // 科系代碼
    string departmentName ; // 科系名稱
    string dayNight ; // 日間∕進修別
    string level ;  // 等級別
    int studentNum ; // 學生數
    int teacherNum ; // 教師數
    int graduateNum ; // 上學年度畢業生數
    string city ; // 縣市名稱
    string system ; // 體系別
}; // struct SchoolType

struct SchoolName{
  int no ;
  string schoolName ;  // 學校名稱
};

struct Department{
  int no ; // 序號
  string departmentName ; // 科系名稱
};

class TwoThreeNode{
public :
  vector<vector<SchoolName> > schoolsKey ; // 每個節點最多存兩個key
  TwoThreeNode * parent ;   // 父親節點
  TwoThreeNode * leftChild ; // 左邊節點
  TwoThreeNode * midChild ;  // 中間節點
  TwoThreeNode * rightChild ; // 右邊節點

  TwoThreeNode(){
    parent = NULL ;
    leftChild = NULL ;
    midChild = NULL ;
    rightChild = NULL ;
  } // constructor

   TwoThreeNode( vector<SchoolName> aSchool ) { // 設aSchool為新節點所儲存的資料
    parent = NULL ;
    leftChild = NULL ;
    midChild = NULL ;
    rightChild = NULL ;
    schoolsKey.push_back(aSchool) ;
   } // constructor

}; // class TwoThreeNode


class TwoThreeTree{
  public :
      TwoThreeNode * root ;  // 根結點

      void twoThreeInsert( SchoolName aSchool, TwoThreeNode * &temp ) ; // 插入新資料
      void sortThreeKey( vector<vector<SchoolName> > & tempKey );  // 將三個鍵值key做排序
      int getHeight( TwoThreeNode * temp );  // 取得節點temp的高度
      void split( vector<SchoolName> newKey , TwoThreeNode * splitNode, TwoThreeNode * leftLeft,TwoThreeNode * leftRight,
                  TwoThreeNode * rightLeft, TwoThreeNode * rightRight ) ;
      // newKey是要新增至splitNode的節點，但splitNode已滿，所以要分裂splitNode這個節點，
      //若在這次分裂之前，已經對splitNode的子節點分裂過，那後面4個參數為子節點分裂後的指標，若之前沒分裂過，則傳入NULL
      void traversal( TwoThreeNode * temp );
      void printRoot( vector<SchoolType> sch);  // 印出根節點的資料
      vector<int> searchCollege( string collegeName  ) ;
      int numOfNode( TwoThreeNode * temp ) ;
      int sizeOfTree( TwoThreeNode * walk );
      int numOfKey( TwoThreeNode * walk) ;

  TwoThreeTree(){
    root = NULL ;
  } // constructor
};


class AVLNode{ // AVL樹中的一個節點
public :
  vector<Department> departmentKey ;
   int height ;  // 節點的高度
   AVLNode * leftChild ;
   AVLNode * rightChild ;


   AVLNode() {
     leftChild = NULL ;
     rightChild = NULL ;
     height = 0 ;
   } // constructor

   AVLNode( Department aDepartment) {
     leftChild = NULL ;
     rightChild = NULL ;
     departmentKey.push_back(aDepartment) ;
     height = 1 ;
   } // constructor
}; // class AVLNode

class AVLTree{
public :

  AVLNode * root ; // 樹根
  AVLNode * AVLinsert( Department aDepartment, AVLNode * temp) ;
  int getBalanceFactor( AVLNode * node ) ;
  AVLNode * rotateRR( AVLNode * node ) ;
  AVLNode * rotateLL( AVLNode * node ) ;
  AVLNode * rotateRL( AVLNode * node ) ;
  AVLNode * rotateLR( AVLNode * node ) ;
  int getHeight( AVLNode * node ) ;
  void printRoot( vector<SchoolType> sch ) ;
  int numOfNode( AVLNode * avl) ;
  vector<int> searchDepartment( string departmentName  ) ;
  int sizeOfTree(AVLNode * walk);

  AVLTree(){
    root = NULL ;
  }
};


int ReadCommand() ;  // 讀Command，若是0就直接結束
int reCommand() ;
int commandIsTwo(  AVLTree avl, vector<SchoolType> sch  ) ;
void ReadCollegeAndDepartment( string & collegeName, string & departmentName ) ;
void Enter() ;      // 讀到'\n'為止
bool ReadFile( vector<SchoolType> & sch, string & fileId ) ;
void ReadInputFileName( string & fileId,string & inputFullName ) ; // 讀檔案編號
bool OpenInputFile( string & fileId,string & inputFullName,fstream & inputFile ) ; // 打開檔案
void ReadInputData( fstream & file, vector<SchoolType> & sch ) ; // 讀檔案資料
string ReadString(fstream & file) ; // 讀file裡的一個字串
int StringToInt( string str ) ; // 將字串轉成數字
bool IsDigit( char ch ); // 判斷ch是否為數字
void searchSchoolAndDepartment( string collegeName, TwoThreeTree tt, string departmentName, AVLTree avl, vector<SchoolType> sch ) ;
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
    AVLTree gAvl ;
    bool firstDone = false, secondDone = false, thirdDone = false ;

    while ( command != 0 ) {
        switch(command){
            case 0 : break ;
            case 1 : {

                sch.clear() ; // 清空資料
                secondDone = false ;
                thirdDone = false ;

                while ( ! ReadFile(sch, fileId) ) { // 若讀到的fileId為"0"，則會回傳false，再重新讀command
                    if ( reCommand() == 0 ) // 重新讀command
                    return 0 ; // command為0，則直接結束
                } // while

                TwoThreeTree twoThree ;

                for ( int i = 0 ; i < sch.size() ; i++ ) { // 一個一個新增到23樹中
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
      case 2 : {

        if( ! firstDone ) {
            cout << "### Choose 1 first. ###" << endl ;
            break ;
        }
        AVLTree avl ;

        for ( int i = 0 ; i < sch.size() ; i++ ) {
           Department aDepartment ;
           aDepartment.no = sch[i].no ;
           aDepartment.departmentName = sch[i].departmentName ;
           avl.root = avl.AVLinsert(aDepartment, avl.root) ;
        } // for

        gAvl = avl ;
        cout << "Tree Height =  " << avl.root->height << endl  ;
        avl.printRoot(sch) ;


        int numOfNode = avl.numOfNode(avl.root) ;
        cout << "Num of AVL Node = " << numOfNode << endl ;
        cout << "SIZE Of AVLTree = " << avl.sizeOfTree(avl.root) << "bytes. " << endl ;

        secondDone = true ;
        break ;

    } // else if command == 2
    case 3 : {

        if( ! firstDone ) {
            cout << "### Choose 1 first. ###" << endl ;
            break ;
        }
        else if ( ! secondDone ) {
             cout << "### Choose 2 first. ###" << endl ;
            break ;
        }
       string collegeName, departmentName ;
       ReadCollegeAndDepartment( collegeName, departmentName ) ;
       searchSchoolAndDepartment(collegeName, gTwoThree, departmentName, gAvl,sch ) ;
       break ;


    } // case 3
    case 4 : {



    } // case 4
    default :
      cout << "### command does not exist  ###" << endl ;        } // switch command
     command = ReadCommand() ;
  } // while(command != 0)

    return 0;
} // main()

int ReadCommand(){  // 讀command
  cout << "*******  Search Tree Utilities   ******" << endl ;
  cout << "* 0. QUIT                           ***" << endl ;
  cout << "* 1. Build 2-3 tree                 ***" << endl ;
  cout << "* 2. Build AVL tree                 ***" << endl ;
  cout << "* 3. Intersection Query             ***" << endl ;
  cout << "************************************" << endl ;
  cout << "Input a choice(0,1,2,3) : "  ;
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
  else if ( command == 2 || command == 3 ) {
    cout << "### Choose 1 first. ### " << endl ;
    return reCommand() ;
  } // if
  else {
    cout << "### command does not exist  ###" << endl ;
    return reCommand() ;
  } // else if

} // reCommand()


int commandIsTwo( AVLTree avl, vector<SchoolType> sch ){
    int command = 2 ;
    while( command == 2 ) {
      cout << "### AVL Tree has been built. ###" << endl ;
      cout << "Tree Height =  " << avl.root->height << endl ;
      avl.printRoot(sch) ;
      command = ReadCommand() ;
    } // while
    return command ;
}


void Enter(){        // 讀到'\n'為止
  char enter ;
  cin.get(enter) ;
  while( enter != '\n' )
    cin.get(enter) ;
} // Enter()

bool ReadFile( vector<SchoolType> & sch, string & fileId ){
  fstream inputFile ;
  string inputFullName ;
  ReadInputFileName( fileId,inputFullName ) ;   // 讀檔案編號
  if ( ! OpenInputFile( fileId, inputFullName, inputFile ) )  // 開啟檔案，若檔案編號是0則直接結束重新讀command
    return false ;
  else {
    ReadInputData(inputFile,sch) ;
    inputFile.close();
    return true ;
  } // else
} //  ReadFile()

void ReadInputFileName( string & fileId,string & inputFullName ){
  cout << "Input a file number(eg.201,202,203......)[0]Quit : " ;
  cin >> fileId ;
  char ch ;
  cin.get(ch);
  if ( ch != '\n')
    Enter() ;
  inputFullName = "input.txt" ;
  inputFullName = inputFullName.insert( 5,fileId );
} // ReadInputFileName

bool OpenInputFile( string & fileId,string & inputFullName,fstream & inputFile ){
  if ( fileId.compare("0") == 0 )  // 如果編號是0，直接結束，重新讀command
   return false ;
  else {
    inputFile.open( inputFullName.c_str(), ios::in ) ;
    while ( ! inputFile ) {    // 做到檔案成功開啟
      cout << "### " << inputFullName << " does not exist ### " << endl ;
      fileId = "" ;
      ReadInputFileName( fileId,inputFullName ) ;
      if ( fileId.compare("0") == 0 )   // 如果編號是0，直接結束，重新讀command
        return false ;
      inputFile.open( inputFullName.c_str(), ios::in) ;
    } // while
  } // else
  return true ;
} // OpenInputFile()

void ReadInputData( fstream & file, vector<SchoolType> & sch ){
  string line ;
  for ( int i = 0 ; i < 3 ; i++ ) // 讀掉前3列
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



int StringToInt( string str ){  // 把string換成int
  int sum = 0 ;
  for ( int i = 0 ; i < str.length() ; i++ ) {
    if ( IsDigit( str[i]) ) {
      int num = str[i] - '0' ;
      sum = sum*10 + num ;
    } // if
  } // for

  return sum ;
} // StringToInt()

bool IsDigit( char ch ) { // 是不是數字
  if ( ch >= '0' && ch <= '9')
    return true ;
  else
    return false ;
} // IsDigit()


void TwoThreeTree :: twoThreeInsert( SchoolName aSchool, TwoThreeNode * & twoThreeNode ) { // 新增aSchool到23樹中

  TwoThreeNode * temp = twoThreeNode ;
  vector<SchoolName> newKey ;
  newKey.push_back( aSchool ) ;

  if ( twoThreeNode == NULL ) {
      twoThreeNode = new TwoThreeNode(newKey) ; // 新增一個節點
  } // if
  else if ( temp ->schoolsKey.size() == 1 ) {  // key只有一個
    if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) == 0 ){ // aSchool的學校名稱與temp所指向節點的的一個鍵值相同
        temp->schoolsKey[0].push_back(aSchool) ;                                // 將aShool新增至這個鍵值的最尾端
    } // if 一樣名字
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) < 0 ) { // aSchool的學校名稱小於temp所指向節點的的一個鍵值
       if( temp->leftChild == NULL ) { // temp已經走到葉節點了
          temp->schoolsKey.insert(temp->schoolsKey.begin(), newKey ) ; // 將用aSchool建立的鍵值newKey插入在temp的鍵值的最前面
       } // if
       else {
         twoThreeInsert(aSchool, temp->leftChild ) ; // 還沒走到葉節點，繼續往下走
       } // else
    } // else if
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) > 0 ) { // aSchool的學校名稱大於temp所指向節點的的一個鍵值
       if( temp->rightChild == NULL ) { // temp已經走到葉節點了
          temp->schoolsKey.push_back(newKey) ; // 將用aSchool建立的鍵值newKey新增在temp的鍵值的最尾端
       } // if
       else {
         twoThreeInsert(aSchool, temp->rightChild ) ; // 還沒走到葉節點，繼續往下走
       } // else
    } // else if

  } // else if key 有一個
  else if ( temp ->schoolsKey.size() == 2 ) { // 走到2個key的節點
    if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) == 0 ){
        temp->schoolsKey[0].push_back(aSchool) ;
    } // if 一樣名字
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[1][0].schoolName) == 0 ) {
        temp->schoolsKey[1].push_back(aSchool) ;
    } // else if
    else if ((aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) < 0 ) {
       if( temp->leftChild == NULL ) { // 已經走到葉節點了
          split( newKey, temp, NULL, NULL, NULL,NULL) ;
          // 分裂
       } // if
       else {
        twoThreeInsert(aSchool, temp->leftChild ) ;
       } // else
    } // else if
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[0][0].schoolName) > 0 && (aSchool.schoolName).compare(temp->schoolsKey[1][0].schoolName) < 0) {
       if( temp->midChild == NULL ) { // 已經走到葉節點了
          split(newKey,temp, NULL, NULL, NULL,NULL) ;
       } // if
       else {
        twoThreeInsert(aSchool, temp->midChild ) ;
       } // else
    } // else if
    else if ( (aSchool.schoolName).compare(temp->schoolsKey[1][0].schoolName) > 0 ) {
       if( temp->rightChild == NULL ) { // 已經走到葉節點了
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

  vector<vector<SchoolName> > tempKeys ; // 用一個暫時的vector存進3個key，讓他們由小到大排序
  tempKeys.push_back(splitNode->schoolsKey[0]) ;
  tempKeys.push_back( splitNode->schoolsKey[1] ) ;
  tempKeys.push_back(newKey) ;
  sortThreeKey(tempKeys) ; // 將三個key排序

  // cout << "SORTED " << tempKeys[0][0].num << "  " << tempKeys[1][0].num << "  " << tempKeys[2][0].num << endl ;

  TwoThreeNode * newNode = new TwoThreeNode( tempKeys[0] ) ; // 用最小的key new一個新的節點
  splitNode->schoolsKey.clear() ; // 將原本要分裂的點先清空
  splitNode->schoolsKey.push_back( tempKeys[2]) ; // 在存進3個key中最大的那一個

  //splitNode->midChild = NULL ;

  if ( leftLeft != NULL ) {  // 不是第一次分裂節點，先把之前分裂好的點接上

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


  if ( splitNode->parent == NULL ) { // 若要分裂的節點沒有父節點，表示會有一個新的root，存中間的鍵值

    root = new TwoThreeNode( tempKeys[1]) ; // 用中間鍵值新增一個新的根節點
    root->leftChild = newNode ;       // root的左小孩是剛剛new的新節點，鍵值最小的那個
    newNode->parent = root ;
    root->rightChild = splitNode ;   // root的右小孩是原本要分裂的那個節點
    splitNode->parent = root ;
  } // else if
  else if ( splitNode->parent->schoolsKey.size() == 1 ) { // 要分裂的點的父節點只有一個鍵值
    TwoThreeNode * parentOfSplit = splitNode->parent ;

    if ( ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[0][0].schoolName) < 0 ) {  // splitNode是一parentOfSplit的leftChild，是左節點要分裂
      parentOfSplit->schoolsKey.insert( parentOfSplit->schoolsKey.begin(), tempKeys[1]) ;  // 將排序過後位在中間的key插入在父節點的key的第一個位置

      // 因為前面是把最大的key放在splitNode，最小的key放在newKey，而splitNode又是左節點，左節點應該要放最小值，
      // 所以把左節點改為newNode、中間節點改為splitNode，而右節點不用動到
      parentOfSplit->leftChild = newNode ;  // 父節點的左小孩是newNode，最小的key
      newNode->parent = parentOfSplit ;
      parentOfSplit->midChild =splitNode ; // 父節點的中間小孩是splitNode，最大的key
      splitNode->parent = parentOfSplit ;

    } // if split the leftChild
    else if ( ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[0][0].schoolName) > 0 ) { // splitNode是一parentOfSplit的rightChild，是右節點要分裂
      parentOfSplit->schoolsKey.push_back(tempKeys[1]) ;  // 將排序過後位在中間的key新增至父節點的key的最尾端

      // 因為前面是把最大的key放在splitNode，而splitNode又是右節點，所以就不用再動了，因此需要動到的只有父節點的中間小孩，為最小的key
      parentOfSplit->midChild = newNode ; // 父節點的中間小孩是newNode，最小的key
      newNode->parent = parentOfSplit ;

    } // else if

  } // else if
  else if ( splitNode->parent->schoolsKey.size() == 2 ) { // 要分裂的點的父節點也有兩個鍵值，表示要繼續分裂

    TwoThreeNode * parentOfSplit = splitNode->parent ;

    if (  ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[0][0].schoolName) < 0 ) { // 要分裂的點是leftChild

      TwoThreeNode * LL = newNode ;
      TwoThreeNode * LR = splitNode ;
      TwoThreeNode * RL = parentOfSplit->midChild ;
      TwoThreeNode * RR = parentOfSplit->rightChild ;
      split(tempKeys[1], splitNode->parent, LL, LR, RL, RR ) ;
    } // if
    else if (  ( tempKeys[1][0].schoolName).compare(parentOfSplit->schoolsKey[1][0].schoolName) > 0 ) { // 在最右邊的點要分裂
      TwoThreeNode * LL = parentOfSplit->leftChild ;
      TwoThreeNode * LR = parentOfSplit->midChild ;
      TwoThreeNode * RL = newNode ;
      TwoThreeNode * RR = splitNode ;
      split(tempKeys[1], splitNode->parent, LL, LR, RL, RR ) ;

    } // else if
    else{  // 要分裂的點是midChild
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
        cout << "[" << sch[rootIndex].no << "] " ; // 序號
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
          cout << "[" << sch[rootIndex].no << "] " ; // 序號
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
          cout << "[" << sch[rootIndex].no << "] " ; // 序號
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
    else{ // 有兩個鍵值
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


AVLNode * AVLTree :: AVLinsert( Department aDepartment, AVLNode * avlNode ) {

  if ( avlNode == NULL ) {
    avlNode = new AVLNode(aDepartment) ;
    return avlNode ;
  } // if ( root == NULL )
  else if ((aDepartment.departmentName).compare( avlNode->departmentKey[0].departmentName) == 0 ){ // 一樣科系
    avlNode->departmentKey.push_back(aDepartment) ;
    return avlNode ;
  } // else if
  else if ( (aDepartment.departmentName).compare( avlNode->departmentKey[0].departmentName) < 0 ) {
    avlNode->leftChild = AVLinsert( aDepartment, avlNode->leftChild ) ;
  } // else if
  else if ( (aDepartment.departmentName).compare( avlNode->departmentKey[0].departmentName) > 0 ) {
    avlNode->rightChild = AVLinsert( aDepartment, avlNode->rightChild ) ;
  } // else if

   avlNode->height = 1 + Max( getHeight(avlNode->leftChild), getHeight(avlNode->rightChild) );

   int balanceFactor = getBalanceFactor(avlNode) ;

   if ( balanceFactor >= -1 && balanceFactor <= 1 )   // 不用做旋轉
     return avlNode ;
   else if ( balanceFactor < -1 && getBalanceFactor(avlNode->rightChild) < 0 ) {  // RotateRR
     return rotateRR( avlNode );
   } // else if
   else if ( balanceFactor > 1 && getBalanceFactor(avlNode->leftChild) > 0 ) {  // RotateLL
     return rotateLL( avlNode );
   } // else if
   else if ( balanceFactor < -1 && getBalanceFactor(avlNode->rightChild) > 0 ) {  // RotateRL
     return rotateRL( avlNode );
   } // else if
   else if ( balanceFactor > 1 && getBalanceFactor(avlNode->leftChild) < 0 ) {  // RotateLR
     return rotateLR( avlNode );

   } // else if
} // AVLTree :: AVLinsert()

AVLNode * AVLTree :: rotateRR( AVLNode * node ) {
  AVLNode * newParent = node ->rightChild ;
  node->rightChild = newParent->leftChild ;
  newParent->leftChild = node ;

  node->height = 1 + Max( getHeight(node->leftChild), getHeight(node->rightChild)  ) ;
  newParent->height = 1 + Max( getHeight(newParent->leftChild), getHeight(newParent->rightChild)  ) ;
  return newParent ;
} // rotateRR()

AVLNode * AVLTree :: rotateLL( AVLNode * node ) {
  AVLNode * newParent = node ->leftChild ;
  node->leftChild = newParent->rightChild ;
  newParent->rightChild = node ;

  node->height = 1 + Max( getHeight(node->leftChild), getHeight(node->rightChild)  ) ;
  //cout << "node->height = " << node->height << endl ;
  newParent->height = 1 + Max( getHeight(newParent->leftChild), getHeight(newParent->rightChild)  ) ;
  //cout << "newParent->height = " << newParent->height << endl ;
  return newParent ;
} // rotateLL()

AVLNode * AVLTree :: rotateRL( AVLNode * node ) {

  node->rightChild = rotateLL( node->rightChild ) ; // 先變成RR型態
  return rotateRR(node) ;
} // rotateRR()

AVLNode * AVLTree :: rotateLR( AVLNode * node ) {
  node->leftChild = rotateRR( node->leftChild ) ;  // 先變成LL型態
  return rotateLL(node) ;
} // rotateLR()




int AVLTree :: getBalanceFactor( AVLNode * node ) { // 計算node的BF，即左右子樹高度差

  return getHeight(node->leftChild) - getHeight(node->rightChild) ;
} // AVLTree :: calBalanceFactor()

int AVLTree :: getHeight( AVLNode * node ) {
  if ( node == NULL )
    return 0 ;
  else
    return node->height ;
}

void AVLTree :: printRoot( vector<SchoolType> sch ) {
  if ( root == NULL )
    return ;
  int numOfRoot = 0 ;
  for ( int i = 0 ; i < root->departmentKey.size() ; i++ ) {
    numOfRoot++ ;
    cout << numOfRoot << " : " ;
    int rootIndex = root->departmentKey[i].no - 1 ;
    cout << "[" << sch[rootIndex].no << "] " ; // 序號
    cout << sch[rootIndex].schoolName << ", " << sch[rootIndex].departmentName << ", " << sch[rootIndex].dayNight << ", "
          <<  sch[rootIndex].level << ", " << sch[rootIndex].studentNum << endl ;
  } // for
} // printRoot()

vector<int> AVLTree :: searchDepartment( string departmentName ) {

  vector<int> sameNo ;
  AVLNode * avlWalk = root ;
  while( avlWalk != NULL && (avlWalk->departmentKey[0].departmentName).compare( departmentName) != 0 ) {
    if ( departmentName.compare( avlWalk->departmentKey[0].departmentName) < 0 ) {
      avlWalk = avlWalk->leftChild ;
    } // if
    else{
      avlWalk = avlWalk->rightChild ;
    }
  } // while
  if ( avlWalk != NULL ) {
    for( int i = 0 ; i < avlWalk->departmentKey.size() ; i++ ) {
        sameNo.push_back(avlWalk->departmentKey[i].no) ;
    } // for
  } // if
  return sameNo ; // 回傳一樣科系名稱的序號
} // AVLTree :: searchDepartment

void searchSchoolAndDepartment( string collegeName, TwoThreeTree tt, string departmentName, AVLTree avl, vector<SchoolType> sch ) {
  vector<int> collegeNo ;
  vector<int> departmentNo ;
  vector<int> intersectionNo ;

  if ( collegeName == "*" && departmentName == "*" ) {     // 要尋找的學校名稱跟科系名稱都是don't care
    for( int i = 0 ; i < sch.size() ; i++ )
        intersectionNo.push_back( sch[i].no ) ;
  } // if
  else if ( collegeName == "*" ) {  // 只有學校名稱是don't care
    intersectionNo = avl.searchDepartment( departmentName ) ; // 在avl樹中尋找與departmentName相同的科系名稱
  } // if
  else if( departmentName == "*" ) {  // 只有科系名稱是don't care
    intersectionNo = tt.searchCollege( collegeName ) ; // 在23樹中尋找與collegeName相同的學校名稱
  } // if
  else{
    collegeNo = tt.searchCollege(collegeName) ;
    departmentNo = avl.searchDepartment( departmentName ) ;

    for( int i = 0 ; i < collegeNo.size() ; i++ ) {
        for( int j = 0 ; j < departmentNo.size() ; j++ ) {
           if ( collegeNo[i] == departmentNo[j] ) {  // 將相同的序號存進intersectionNo中
              intersectionNo.push_back( collegeNo[i] ) ;
           } // if
        } // for
    } // for
  } // if



  int numOfIntersection = 0 ;
  for( int i = 0 ; i < intersectionNo.size() ; i++ ) {
    numOfIntersection++ ;
    int sameIndex = intersectionNo[i] - 1 ;
    cout << numOfIntersection << " : " ;
    cout << "[" << sch[sameIndex].no << "] " ; // 序號
    cout << sch[sameIndex].schoolName << ", " << sch[sameIndex].departmentName << ", " << sch[sameIndex].dayNight << ", "
          <<  sch[sameIndex].level << ", " << sch[sameIndex].studentNum << endl ;
  } // for


} // searchSchoolAndDepartment

int AVLTree :: numOfNode( AVLNode * temp ){
  if ( temp == NULL )
    return 0 ;
  return 1 + numOfNode( temp->leftChild ) + numOfNode( temp->rightChild) ;

} //AVLTree :: numOfNode( AVLNode * temp )

int AVLTree :: sizeOfTree( AVLNode * walk ){
  if( walk == NULL )
    return 0 ;
  else{
    int sizeOfNode = 16 ; // 一個pointer占8個byte，1個avlNode有2個pointer
    for( int i = 0 ; i < walk->departmentKey.size() ; i++ ) {
      int sizeOfString = walk->departmentKey[i].departmentName.size();
      int sizeOfNo = sizeof(walk->departmentKey[i].no) ;
      sizeOfNode = sizeOfNode + sizeOfString + sizeOfNo ;
    } // for
    return sizeOfNode + sizeOfTree(walk->leftChild) + sizeOfTree(walk->rightChild) ;
  } // else

} // sizeOfTree( AVLNode * walk )

int TwoThreeTree :: sizeOfTree( TwoThreeNode * walk ){
  if ( walk == NULL )
    return 0 ;
  else if ( walk->schoolsKey.size() == 1 ) {
    int sizeOfNode = 32 ; // 一個pointer占8個byte，1個aTwoThreeNode有4個pointer
    for( int i = 0 ; i < walk->schoolsKey[0].size() ; i++ ) {
      int sizeOfString = walk->schoolsKey[0][i].schoolName.size();
      int sizeOfNo = sizeof(walk->schoolsKey[0][i].no) ;
      sizeOfNode = sizeOfNode + sizeOfString + sizeOfNo ;
    } // for
      return sizeOfNode + sizeOfTree(walk->leftChild) + sizeOfTree(walk->rightChild) ;
  } // else if
  else{
    int sizeOfNode = 16 ; // 一個pointer占4個byte，1個aTwoThreeNode有4個pointer
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
