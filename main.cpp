#include <iostream>
#include <fstream>


using namespace std;
#define MAX 15
int **array;    // mảng để lưu đỉnh kề nhau
int *cov;   // color of vertex : mã màu của từng đỉnh
int number_student;  // số lượng sinh viên
int number_subject;    // số lượng môn học
string *subjects;
ifstream file_students("students1.txt");     // đầu vào danh sách học sinh
ifstream file_subjects("subjects1.txt");     // đầu vào danh sách môn học
ofstream file_kq("LichThi.txt");            // đầu ra danh sách ca thi


struct Student *students;

struct Student
{
    string name;
    string *student_subjects;
    int amount;
    Student()
    {
        name="";
        amount=0;
    }
    Student(string ten,int so_luong)
    {
        name=ten;
        amount=so_luong;
        student_subjects=new string[amount];
    }
    void setSubject(string s,int i)
    {
        student_subjects[i]=s;
    }
    void show()
    {
        cout<<name<<endl<<endl;
        for(int i=0;i<amount;i++)
        {
            cout<<"\tMon thu "<<i+1<<" : "<<student_subjects[i]<<endl;
        }
        cout<<endl;
    }
};



bool check(int i,int color)
{
    for(int j=0;j<number_subject;j++)
    {
        if(array[i][j]==1&&cov[j]==color) return false;        // kiểm tra nếu đinh i kề đình j( j đã tô mà color) thì i không thể tô màu color nữa
    }
    return true;
}
int color1(int color)      // hàm tô 1 mã màu cho nhiều đỉnh nhất có thể
{
    int count=0;    // đếm bao nhiêu đỉnh được tô bằng màu color
    for(int i=0;i<number_subject;i++)
    {
        if(cov[i]==0 && check(i,color))   // kiểm tra đỉnh i chưa tô và tô được màu color thì tô
        {
            cov[i]=color;                       //tô màu cho đỉnh i
            count++;
        }
    }
    return count;
}
void colorAll()     // hàm tô màu tất cả các đỉnh
{
    cov=new int[number_subject];
    for(int i=0;i<number_subject;i++)    cov[i]=0;           // ban đầu khởi gán cho các đỉnh = 0 ( chưa tô đỉnh nào cả)
    int color_number=0;
    int count=0;
    while(count<number_subject)  // đảm bảo tô hết các đỉnh
    {
        color_number++;
        count+=color1(color_number);
    }
    cout<<"\n\n--------------Da xep xong lich thi----------------"<<endl<<endl;
}
void readStudents()
{
    char temp[50];
    string name;
    int i=0;
    number_student=0;
    file_students.getline(temp,50);

    // lấy số lượng sinh viên
    while(temp[i]){
        number_student*=10;
        number_student+=temp[i]-48;
        i++;
    }
    students=new Student[number_student];   // khởi tạo bộ nhớ
    i=0;
    int index=0; // vị trí sinh viên thứ mấy
    int sub_number=0; // số lượng môn học của từng sinh viên

    //lấy thông tin môn học của các sinh viên
    while(file_students.getline(temp,50)){
        if(temp[0]=='-'){
           i=0;
           index++;
           continue;
        }
        if(i==0)    name=temp;
        else if(i==1){
            int k=0;
            while(temp[k]){
                sub_number*=10;
                sub_number+=temp[k]-48;
                k++;
            }
            students[index]= Student(name,sub_number);
            sub_number=0;
        }
        else{
            students[index].setSubject(temp,i-2);   // gán giá trị môn học cho sinh viên ngay vị trí i-2 ( vì bắt đầu đọc giá trị môn học từ hàng thứ 2)
        }
        i++;
    }
    cout<<"\n--------------Doc danh sach sinh vien thanh cong--------------"<<endl<<endl;
}
void readSubjects()
{
    char temp[50];
    file_subjects.getline(temp,50);
    int i=0;
    while(temp[i])
    {
        number_subject*=10;
        number_subject+=temp[i]-48;
        i++;
    }
    subjects=new string[number_subject];
    int index=0;
    while(file_subjects.getline(temp,50))
    {
        subjects[index]=temp;
        index++;
    }
    cout<<"--------------Doc danh sach mon hoc thanh cong----------------"<<endl<<endl;
}
int getIndexSubject(string s)
{
    for(int i=0;i<number_subject;i++)
    {
        if(s==subjects[i]) return i;
    }
    return NULL;
}
void putArray()
{
    array=new int*[number_subject];
    for(int i=0;i<number_subject;i++)
    {
        array[i]=new int[number_subject];
        for(int j=0;j<number_subject;j++)
        {
            array[i][j]=0;
        }
    }
    for(int i=0;i<number_student;i++)
    {
        for(int j=0;j<students[i].amount-1;j++)
        {
            for(int k=j+1;k<students[i].amount;k++)
            {
                int num1=getIndexSubject(students[i].student_subjects[j]);
                int num2=getIndexSubject(students[i].student_subjects[k]);
                array[num1][num2]=array[num2][num1]=1;

            }
        }
    }
    cout<<"--------------Dua du lieu vao mang thanh cong--------------"<<endl<<endl;
}


void viewStudents()
{
    cout<<endl<<endl<<"--------------Danh sach sinh vien--------------"<<endl<<endl;
    for(int i=0;i<number_student;i++)
    {
        cout<<"Hoc sinh thu "<<i+1<<" : ";
        students[i].show();
    }
}


void viewSubjects()
{
    cout<<endl<<endl<<"--------------Danh sach mon hoc--------------"<<endl<<endl;
    for(int m=0;m<number_subject;m++)
    {
        cout<<m+1<<" : "<<subjects[m]<<endl;
    }

}


void viewArray()
{
    cout<<endl<<endl<<"--------------Du lieu mang--------------"<<endl<<endl<<"\t";
    for(int i=0;i<number_subject;i++)
    {
        cout<<i+1<<"\t";
    }

    for(int i=0;i<number_subject;i++)
    {   cout<<"\n\n"<<i+1<<"\t";
        for(int j=0;j<number_subject;j++)
        {
            cout<<array[i][j]<<"\t";
        }
    }
}

void viewColorSubjects()
{
    cout<<"\n--------------Ma mau cua cac mon hoc--------------\n";
    for(int i =0;i<number_subject;i++)
    {
        cout<<"\n\tMa mau : "<<cov[i]<<" | "<<subjects[i];
    }
}
void writeFile()
{
    int n=0;
    int k=1;
    while(n<number_subject)
    {
        file_kq<<"Ca : "<<k<<endl;
        for(int i=0;i<number_subject;i++)
        {
            if(cov[i]==k)
            {
                file_kq<<"      "<<subjects[i]<<endl;
                n++;
            }
        }
        k++;

    }
    cout<<endl<<endl<<"--------------Lich thi da duoc dua vao file--------------"<<endl<<endl;

}
void viewExamSchedule()
{
    int n=0;
    int k=1;
    while(n<number_subject)
    {
        cout<<"\nCa : "<<k<<endl;
        for(int i=0;i<number_subject;i++)
        {
            if(cov[i]==k)
            {
                cout<<"      "<<subjects[i]<<endl;
                n++;
            }
        }
        k++;
    }
}
void deleteMemory()
{
    for(int i = 0; i < number_subject; i++)
    {
        delete[] array[i];
    }

    delete[] array;

    delete[] students;

    delete[] subjects;

    delete[] cov;
}

int main()  {

    readSubjects();

    viewSubjects();

    readStudents();

    viewStudents();

    putArray();

    viewArray();

    colorAll();

    viewColorSubjects();

    writeFile();

    viewExamSchedule();

    deleteMemory();

    return 0;
}

