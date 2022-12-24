#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class BirthDate{
public:
    int year;//年
    int month;//月
    int day;//日
    BirthDate();
    BirthDate(int y,int m,int d):year(y),month(m),day(d){}
    friend istream& operator>>(istream &in,BirthDate &b);
    friend ostream& operator<<(ostream &out,BirthDate &b);
    void change(int,int,int);//修改
};
class Person
{
protected:
    string name;//姓名
    string sex;//性别
    BirthDate birth;//生日
public:
    Person();
    Person(string n,string s,int y,int m,int d):birth(y,m,d),name(n),sex(s){}
    ~Person();
    virtual void display();//输出
    void input();//输入
};
class Student:public Person//学生类
{
protected:
    string id;//学号
    string course[5];//五门课名
    double score[5];//五门成绩
    double total;//总分
    static int N;//统计学生数量
public:
    Student();
    Student(string n,string s,int y,int m,int d,string i,string course[5],double score[5],double t);
    ~Student();
    friend istream& operator>>(istream &in,Student &s);
    friend ostream& operator<<(ostream &out,Student &s);
    void display();//打印终端
    void input(Student*);//输入并写入文件
};
class Undergraduate:public Student//大学生类
{
private:
    string major;//专业名
    double gpa;//绩点
    static int N;//统计学生数量
public:
    Undergraduate();
    Undergraduate(string n,string s,int y,int m,int d,string i,string course[5],double score[5],double t,string major):Student(n,s,y,m,d,i,course,score,t),major(major){gpa=0;}
    ~Undergraduate();
    friend istream& operator>>(istream &in,Undergraduate &s);
    friend ostream& operator<<(ostream &out,Undergraduate &s);
    void display(); //显示
    void input(Undergraduate*);//导入学生成绩等信息
    void add(Undergraduate*);//增加
    void remove(Undergraduate*);//删除
    friend void search(Undergraduate*);//查找
    void change(Undergraduate*);//修改
    bool unique(const Undergraduate*,const string);//判断重复学号
    friend void sort1(const Undergraduate *s);//排名
    friend void sling(const Undergraduate*);//挂科
    void menu(Undergraduate*); //目录
};
//BirthDate类
BirthDate::BirthDate()
{
    year=2000;
    month=1;
    day=1;
}
istream& operator>>(istream &in,BirthDate &b)
{
    in>>b.year>>b.month>>b.day;
    return in;
}
ostream& operator<<(ostream &out,BirthDate &b)
{
    out<<b.year<<" "<<b.month<<" "<<b.day;
    return out;
}
void BirthDate::change(int y,int m,int d)//修改
{
    year=y;
    month=m;
    day=d;
}
//Person类
Person::Person()
{
    name='0';
    sex='0';
}
Person::~Person()
{
}
void Person::display()//输出
{
    cout<<name<<" "<<sex<<" ";
    cout<<birth<<" ";
}
void Person::input()//输入
{
    cin>>name>>sex;
    cin>>birth;
}
//Student类
int Student::N=0;
Student::Student()
{
    id='0';
    for(int i=0;i<5;i++)
    {
        course[i]='0';
        score[i]=0;
    }
    total=0;
}
Student::Student(string n,string s,int y,int m,int d,string i,string c[5],double sc[5],double t):Person(n,s,y,m,d),id(i),total(t)
{
    for(int i=0;i<5;i++)
    {
        course[i]=c[i];
        score[i]=sc[i];
    }
}
Student::~Student()
{
}
istream& operator>>(istream &in,Student &s)
{
    in>>s.name>>s.sex>>s.birth;
    in>>s.id;
    in>>s.course[0]>>s.course[1]>>s.course[2]>>s.course[3]>>s.course[4];
    in>>s.score[0]>>s.score[1]>>s.score[2]>>s.score[3]>>s.score[4];
    return in;
}
ostream& operator<<(ostream &out,Student &s)
{
    out<<s.name<<" "<<s.sex<<" "<<s.birth<<" ";
    out<<s.id<<" "<<s.course[0]<<" "<<s.score[0]<<" ";
    out<<s.course[1]<<" "<<s.score[1]<<" "<<s.course[2]<<" "<<s.score[0]<<" ";
    out<<s.course[3]<<" "<<s.score[3]<<" "<<s.course[4]<<" "<<s.score[4];
    return out;
}

void Student::display()
{
    Student s[N];
    cout<<"name  sex  birth  SN  class1  score1  class2  score2  class3  score3  class4  score4  class5  score5"<<endl;
    ifstream infile("student.dat");
    if(!infile)
    {
        cout<<"open error!"<<endl;
    }
    for(int i=0;i<N;i++)
    {
        infile>>s[i];
        cout<<s[i]<<endl;
    }
    infile.close();
}
void Student::input(Student *s)
{
    int n;
    ofstream outfile("student.dat");
    if(!outfile)
    {
        cout<<"open error!"<<endl;
    }
    cout<<"Please enter the number of imported students:"<<endl;
    cin>>n;
    N=n;
    cout<<"Please enter student information"<<endl;
    cout<<"name  sex  birth  SN  class1  score1  class2  score2  class3  score3  class4  score4  class5  score5"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
        outfile<<s[i]<<endl;
    }
    outfile.close();
}

//Undergradu类
int Undergraduate::N=0;
Undergraduate::Undergraduate()
{
    major='0';
    gpa=0;
}
Undergraduate::~Undergraduate()
{
}
istream& operator>>(istream &in,Undergraduate &s)
{
    in>>s.major;
    in>>s.name>>s.sex>>s.birth;
    in>>s.id>>s.course[0]>>s.score[0];
    in>>s.course[1]>>s.score[1]>>s.course[2]>>s.score[2];
    in>>s.course[3]>>s.score[3]>>s.course[4]>>s.score[4];
    return in;
}
ostream& operator<<(ostream &out,Undergraduate &s)
{
    out<<s.major<<" ";
    out<<s.name<<" "<<s.sex<<" "<<s.birth<<" ";
    out<<s.id<<" "<<s.course[0]<<"\t"<<s.score[0]<<"\t";
    out<<s.course[1]<<"\t"<<s.score[1]<<"\t"<<s.course[2]<<"\t"<<s.score[2]<<"\t";
    out<<s.course[3]<<"\t"<<s.score[3]<<"\t"<<s.course[4]<<"\t"<<s.score[4];
    return out;
}

void Undergraduate::display()
{
    Undergraduate s[N];
    cout<<"major  name  sex  birth  SN  class1  score1  class2  score2  class3  score3  class4  score4  class5  score5"<<endl;
    ifstream infile("Undergraduate.dat");//打开文件
    if(!infile)
    {
        cout<<"open error!"<<endl;
    }
    for(int i=0;i<N;i++)
    {
        infile>>s[i];//写入文件
        cout<<s[i]<<endl;//打印终端
    }
    infile.close();//关闭终端
}
void Undergraduate::input(Undergraduate *s)//输入
{
    int n;
    ofstream outfile("Undergraduate.dat");//打开文件
    if(!outfile)
    {
        cout<<"open error!"<<endl;
    }
    cout<<"Please enter the number of imported students:"<<endl;
    cin>>n;
    if(n<0)
    {
        cout<<"Input error"<<endl;
    }
    s[0].N=n;//统计学生人数
    cout<<"Please enter information such as student grades"<<endl;
    cout<<"major  name  sex  birth  SN  class1  score1  class2  score2  class3  score3  class4  score4  class5  score5"<<endl;
    try
    {
        for(int i=0;i<n;i++)
        {
            cin>>s[i];//输入学生信息
            if(s[i].score[0]<0||s[i].score[0]>100||s[i].score[1]<0||s[i].score[1]>100||s[i].score[2]<0||s[i].score[2]>100||s[i].score[3]<0||s[i].score[3]>100||s[i].score[4]<0||s[i].score[4]>100)
            {
                int a;
                throw a;
            }
            if(s[i].birth.year<=1980||s[i].birth.month<=0||s[i].birth.month>=12||s[i].birth.day<=0||s[i].birth.day>31)
            {
                BirthDate birth;
                throw birth;
            }
            outfile<<s[i]<<endl;//写入文件
        }
        outfile.close();//关闭文件
    }
    catch(int)
    {
        cout<<"The grade entered is illegal"<<endl;
    }
    catch(BirthDate)
    {
        cout<<"It is illegal to enter the date of birth"<<endl;
    }
}
void Undergraduate::add(Undergraduate *s)//增加
{
    int n;
    cout<<"Please enter the number of people you want to add"<<endl;
    cin>>n;
    cout<<"major  name  sex  birth  SN  class1  score1  class2  score2  class3  score3  class4  score4  class5  score5"<<endl;
    ofstream outfile("Undergraduate.dat",ios::app);//打开文件
    if(!outfile)
    {
        cout<<"open error!"<<endl;
    }
    try
    {
        for(int i=N;i<N+n;i++)
        {
            cin>>s[i];//输入学生信息
            if(Undergraduate::unique(s,s[i].id))//判断是否输入重复学号
            {
                cout<<"Please re-enter information such as student grades:"<<endl;
                cin>>s[i];
            }
            if(s[i].score[0]<0||s[i].score[0]>100||s[i].score[1]<0||s[i].score[1]>100||s[i].score[2]<0||s[i].score[2]>100||s[i].score[3]<0||s[i].score[3]>100||s[i].score[4]<0||s[i].score[4]>100)
            {
                int a;
                throw a;
            }
            if(s[i].birth.year<=1980||s[i].birth.month<=0||s[i].birth.month>=12||s[i].birth.day<=0||s[i].birth.day>31)
            {
                BirthDate birth;
                throw birth;
            }
            outfile<<s[i]<<endl;//将学生信息写入文件
        }
        outfile.close();//关闭文件
        N+=n;//增加学生人数
    }
    catch(int)
    {
        cout<<"The grade entered is illegal"<<endl;
    }
    catch(BirthDate)
    {
        cout<<"It is illegal to enter the date of birth"<<endl;
    }
}
void Undergraduate::remove(Undergraduate *s)//删除
{
    int n;
    string id;
    bool flag=false;
    cout<<"Please enter the student ID you want to delete student information:"<<endl;
    while(!flag)
    {
        cin>>id;
        for(int i=0;i<N;i++)
        {
            if(s[i].id==id)//判断是否找到要删除学生学号
            {
                flag=true;
                cout<<"Student grades and other information:"<<endl;
                for(int k=0;k<N;k++) //打印到终端
                {
                    cout<<s[k]<<endl;
                }
                for(int j=i;j<N-1;j++)//往前移1为，覆盖该学生信息
                    s[j]=s[j+1];
                cout<<"Deleted successfully!"<<endl;
                N=N-1;//减少学生人数
                break;
            }
        }
        if(!flag)
        {
            cout<<"The student information is not found, please re-enter it"<<endl;
        }
    }
    ofstream outfile("Undergraduate.dat");//打开文件
    if(!outfile)
    {
        cout<<"open error!"<<endl;
    }
    cout<<"After deletion of the Student Information Table:"<<endl;
    for(int i=0;i<N;i++)
    {
        outfile<<s[i]<<endl;//写入文件
        cout<<s[i]<<endl;//打印终端
    }
    outfile.close(); //关闭文件
}
void search(Undergraduate *s)//查找
{
    string id;
    bool flag=false;
    int i,j,count=0;
    int num[5]={-1};
    int N=s[0].N;
    cout<<"Please enter the student ID for which you want to find student information:"<<endl;
    while(!flag)
    {
        cin>>id;
        for(i=0;i<N;i++)
        {
            if(s[i].id==id)//判断是否查找到该学生信息
            {
                flag=true;
                cout<<"Information about the student:"<<endl;
                cout<<s[i];
                for(j=0;j<5;j++)
                {
                    if(s[i].score[j]<60)
                    {
                        count++;//统计挂科数
                    }
                }
                cout<<"\thave"<<count<<"Courses are unblocked"<<endl;
                break;
            }
        }
        if(!flag)
        {
            cout<<"The student information is not found, please re-enter the student number"<<endl;
        }
    }
}
void Undergraduate::change(Undergraduate *s)//修改
{
    string id;
    bool flag=false;
    cout<<"Please enter the student ID for which you want to change the student's information:"<<endl;
    while(!flag)
    {
        cin>>id;
        for(int i=0;i<N;i++)
        {
            if(s[i].id==id)//判断是否找到要修改的学生
            {
                flag=true;
                cout<<"Student Achievement Information Sheet:"<<endl;
                for(int k=0;k<N;k++)
                {
                    cout<<s[k]<<endl; //打印修改前学生的信息
                }
                cout<<"Please re-enter the student's information:"<<endl;
                cin>>s[i];
                break;
            }
        }
        if(!flag)
        {
            cout<<"The student information is not found, please re-enter the student number:"<<endl;
        }
    }
    ofstream outfile("Undergraduate.dat");//打开文件
    if(!outfile)
    {
        cout<<"open error!"<<endl;
    }
    cout<<"Revised Student Achievement Information Sheet:"<<endl;
    for(int i=0;i<N;i++)
    {
        outfile<<s[i]<<endl;//将修改后学生信息写入文件
        cout<<s[i]<<endl;//将修改后信息打印终端
    }
    outfile.close(); //关闭文件
}
bool Undergraduate::unique(const Undergraduate *s,const string id)//判断重复学号
{
    for(int i=0;i<N;i++)
    {
        if(s[i].id==id)
        {
            cout<<s[i].id<<"already exists, please do not enter student information with duplicate student numbers!"<<endl;
            return true;
        }
    }
    return false;
}
void sort1(const Undergraduate *s)//按学生绩点排序
{
    int i,j,k;
    int N=s[0].N;
    Undergraduate temp,stu[N];
    ifstream infile("Undergraduate.dat");
    if(!infile)
    {
        cout<<"open error!"<<endl;
    }
    for(i=0;i<N;i++)//从文件读
        infile>>stu[i];
    infile.close();
    for(i=0;i<N;i++)//求总分
    {
        stu[i].total=0;
        for(j=0;j<5;j++)
        {
            stu[i].total+=stu[i].score[j];
        }
        stu[i].gpa=(stu[i].total/50.0)-5;//求绩点
    }
    for(i=0;i<N-1;i++)//按学生绩点冒泡排序 从高到低打印到终端
    {
        for(j=0;j<N-1-i;j++)
        {
            if(stu[j].gpa<stu[j+1].gpa)
            {
                temp.name=stu[j].name;temp.sex=stu[j].sex;temp.birth=stu[j].birth;temp.id=stu[j].id;
                temp.name=stu[j].name;temp.total=stu[j].total;temp.gpa=stu[j].gpa;
                for(k=0;k<5;k++)
                {
                    temp.course[k]=stu[j].course[k];
                    temp.score[k]=stu[j].score[k];
                }

                stu[j].name=stu[j+1].name;stu[j].sex=stu[j+1].sex;stu[j].birth=stu[j+1].birth;stu[j].id=stu[j+1].id;
                stu[j].name=stu[j+1].name;stu[j].total=stu[j+1].total;stu[j].gpa=stu[j+1].gpa;
                for(k=0;k<5;k++)
                {
                    stu[j].course[k]=stu[j+1].course[k];
                    stu[j].score[k]=stu[j+1].score[k];
                }

                stu[j+1].name=temp.name;stu[j+1].sex=temp.sex;stu[j+1].birth=temp.birth;stu[j+1].id=temp.id;
                stu[j+1].name=temp.name;stu[j+1].total=temp.total;stu[j+1].gpa=temp.gpa;
                for(k=0;k<5;k++)
                {
                    stu[j+1].course[k]=temp.course[k];
                    stu[j+1].score[k]=temp.score[k];
                }
            }
        }
    }
    ofstream outfile("Undergraduate_score_list.dat");//打开文件
    cout<<"name SN class1 score1 class2 score2 class3 score3 class4 score4 class5 score5\tGPA"<<endl;
    for(i=0;i<N;i++)
    {
        outfile<<stu[i].name<<" "<<stu[i].id<<" ";//写入文件
        cout<<stu[i].name<<" "<<stu[i].id<<" ";//打印终端
        for(j=0;j<5;j++)
        {
            outfile<<stu[i].course[j]<<"\t"<<stu[i].score[j]<<"\t";
            cout<<stu[i].course[j]<<"\t"<<stu[i].score[j]<<"\t";
        }
        outfile<<stu[i].gpa<<endl;
        cout<<stu[i].gpa<<endl;
    }
    outfile.close(); //关闭文件
}
void sling(const Undergraduate *s)//学生挂科情况
{
    int N=s[0].N;
    int i,j,count=0;
    Undergraduate stu[N];
    ifstream infile("Undergraduate.dat");//打开文件
    if(!infile)
    {
        cout<<"open error!"<<endl;
    }
    for(i=0;i<N;i++)//从文件读
        infile>>stu[i];
    infile.close(); //关闭文件
    for(i=0;i<N;i++)
    {
        count=0;
        for(j=0;j<5;j++)
        {
            if(stu[i].score[j]<60)
            {
                count++;//统计挂科数
            }
        }
        cout<<stu[i]<<"\t"<<"have"<<count<<"Courses are unblocked"<<endl; //打印学生成绩等信息和挂科的情况
    }
}
void Undergraduate::menu(Undergraduate *s)//学生成绩管理系统菜单
{
    Undergraduate STU;
    while(1)
    {
        system("color b1");
        cout<<""<<endl;
        cout<<"Welcome to the Student Performance Management System"<<endl;
        cout<<"1 Enter student information"<<endl;
        cout<<"2 Add student information"<<endl;
        cout<<"3 Delete student information"<<endl;
        cout<<"4 Find student information"<<endl;
        cout<<"5 Edit student information"<<endl;
        cout<<"6 Student grade sorting"<<endl;
        cout<<"7 Students' out-of-course status"<<endl;
        cout<<"8 Display student information"<<endl;
        cout<<"9 quit"<<endl;
        cout<<endl;
        int num;
        cin>>num;
        switch(num)
        {
            case 1 :system("CLS");STU.input(s);system("pause");break;
            case 2 :system("CLS");STU.add(s);system("pause");break;
            case 3 :system("CLS");STU.remove(s);system("pause");break;
            case 4 :system("CLS");search(s);system("pause");break;
            case 5 :system("CLS");STU.change(s);system("pause");break;
            case 6 :system("CLS");sort1(s);system("pause");break;
            case 7 :system("CLS");sling(s);system("pause");break;
            case 8 :system("CLS");STU.display();system("pause");break;
            case 9 :system("CLS");cout<<"Thanks for using!";exit(0);system("pause");
            default:system("CLS");printf("Invalid input!\n\n");system("pause");
        }
    }
}
int main()
{
    Undergraduate undergraduate;
    Undergraduate stu[80];
    undergraduate.menu(stu);

    return 0;
}
