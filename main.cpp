#include <iostream>
#include <fstream>
using namespace std;

#define MAX_ANIMALS 100
class Animals {
private:
    int m_X, m_Y;
    int m_Direction;
    int m_Constancy;
    int m_Age;
    int m_BirthStep;
    int m_Cou;
public:
    Animals(int x, int y, int dir, int constant, int birthStep, Animals* parent = nullptr);

    virtual void Move(int W, int H, int step) = 0;///Ready
    virtual void Aging() = 0;///Ready
    virtual bool IsRabbit() const = 0;///Ready
    virtual bool IsHyenas() const = 0;
    virtual bool CanReproduce() = 0; ///Ready

    ///Ready
    int GetX() const;
    int GetY() const;
    int GetDirection() const;
    int GetConstancy() const;
    int GetAge() const;
    int GetBirthStep() const;
    int GetCou() const;

    void SetX(int a);
    void SetY(int a);
    void SetDirection(int a);
    void SetConstancy(int a);
    void SetAge(int a);
    void SetCou(int a);
};

class Rabbit:public Animals{
public:
    Rabbit(int x, int y, int dir, int constant, int birthStep);///Ready
    void Move(int W, int H, int step) override;///Ready
    void Aging() override;///Ready
    bool IsRabbit() const override;///Ready
    bool IsHyenas() const override;
    bool CanReproduce() override;///Ready
};

class Wolfs: public Animals{
public:
    Wolfs(int x, int y, int dir, int constant, int birthStep);///Ready
    void Move(int H, int W, int step) override;///Ready
    void Aging() override;
    bool IsRabbit() const override;
    bool IsHyenas() const override;
    bool CanReproduce() override;
};

class Hyenas: public Animals{
public:
    Hyenas(int x, int y, int dir, int constant, int birthStep);
    void Move(int H, int W, int step) override;///Ready
    void Aging() override;
    bool IsRabbit() const override;
    bool IsHyenas() const override;
    bool CanReproduce() override;
};

///hyenas
Hyenas::Hyenas(int x, int y, int dir, int constant, int birthStep): Animals(x, y, dir, constant, birthStep) {}
void Hyenas::Move(int W, int H, int step){
    int X = GetX();
    int Y = GetY();
    switch (GetDirection()) {
        case 0: //North
            SetY((Y - 2 + H) % H);
            break;
        case 1: //East
            SetX((X + 2 + W) % W);
            break;
        case 2: //South
            SetY((Y + 2 + H) % H);
            break;
        case 3: //Western
            SetX((X - 2 + W) % W);
            break;
    }
    if((step-GetBirthStep())%GetConstancy() == 0){
        SetDirection((GetDirection() + 1) % 4);
    }
}
void Hyenas::Aging() {
    int Age = GetAge();
    SetAge(Age + 1);
}
bool Hyenas::IsRabbit() const {
    return false;
}
bool Hyenas::IsHyenas() const  { return true; }
bool Hyenas::CanReproduce() {
    if(GetCou() >=2){
        return true;
    }
    return false;
}


class Simulator {
private:
    int m_Width , m_Height; //x, y
    int** m_Space;
    int** m_Hyenas;
    Animals** m_Animal;
    mutable int m_CouAnimals;
public:
    Simulator(int width, int height, int num_wolfs, int num_rabbits, int num_hyenas, int** animals);
    void PrintListAnimals();
    void Start(int steps);
    void Print() const;
    void MoveAllAnimals(int step) const;
    void ProcessNutrition() const;
    void ProcessReproduce(int step);
    void AgingAllAnimals() const;
    void AddNewAnimals(int x, int y, int dir, int constant, int birthStep,int step, Animals* parent);
    void ProcessDying();
    void SetSpace();
    void PrintSpace();
    void EnterSpace();
    ~Simulator();

};


///Animals
Animals::Animals(int x, int y, int dir, int constant, int birthStep, Animals *parent): m_X(x), m_Y(y), m_Direction(dir), m_Constancy(constant), m_Age(0), m_BirthStep(birthStep), m_Cou(0){}
int Animals::GetX() const {
    return m_X;
}
int Animals::GetY() const {
    return m_Y;
}
int Animals::GetDirection() const {
    return m_Direction;
}
int Animals::GetConstancy() const {
    return m_Constancy;
}
int Animals::GetAge() const {
    return m_Age;
}
int Animals::GetBirthStep() const {
    return m_BirthStep;
}
int Animals::GetCou() const {
    return m_Cou;
}
void Animals::SetX(int a){
    m_X = a;
}
void Animals::SetY(int a){
    m_Y = a;
}
void Animals::SetDirection(int a){
    m_Direction = a;
}
void Animals::SetConstancy(int a){
    m_Constancy = a;
}
void Animals::SetAge(int a){
    m_Age = a;
}
void Animals::SetCou(int a) {
    m_Cou = a;
}

///Rabbits
Rabbit::Rabbit(int x, int y, int dir, int constant, int birthStep): Animals(x, y, dir, constant, birthStep){
};
void Rabbit::Move(int W, int H, int step) {
    int X = GetX();
    int Y = GetY();
    switch (GetDirection()) {
        case 0: //North
            SetY((Y - 1 + H) % H);
            break;
        case 1: //East
            SetX((X + 1 + W) % W);
            break;
        case 2: //South
            SetY((Y + 1) % H);
            break;
        case 3: //Western
            SetX((X - 1) % W);
            break;
    }
    if((step-GetBirthStep())%GetConstancy() == 0){
        SetDirection((GetDirection() + 1) % 4);
    }
}
void Rabbit::Aging() {
    int Age = GetAge();
    SetAge(Age + 1);
}
bool Rabbit::IsRabbit() const  { return true; }
bool Rabbit::IsHyenas() const  { return false; }
bool Rabbit::CanReproduce() {
    if(GetAge() == 5 || GetAge() == 10){
        return true;
    }
    return false;
}

///Wolfs
Wolfs::Wolfs(int x, int y, int dir, int constant, int birthStep): Animals(x, y, dir, constant, birthStep) {}
void Wolfs::Move(int W, int H, int step){
    int X = GetX();
    int Y = GetY();
    switch (GetDirection()) {
        case 0: //North
            SetY((Y - 2 + H) % H);
            break;
        case 1: //East
            SetX((X + 2 + W) % W);
            break;
        case 2: //South
            SetY((Y + 2 + H) % H);
            break;
        case 3: //Western
            SetX((X - 2 + W) % W);
            break;
    }
    if((step-GetBirthStep())%GetConstancy() == 0){
        SetDirection((GetDirection() + 1) % 4);
    }
}
void Wolfs::Aging() {
    int Age = GetAge();
    SetAge(Age + 1);
}
bool Wolfs::IsRabbit() const {
    return false;
}
bool Wolfs::IsHyenas() const  { return false; }
bool Wolfs::CanReproduce() {
    if(GetCou() >=2){
        return true;
    }
    return false;
}

///Simulator
Simulator::Simulator(int width, int height, int num_wolfs, int num_rabbits, int num_hyenas, int** animals): m_Width(width), m_Height(height), m_CouAnimals(num_wolfs+num_rabbits+num_hyenas), m_Animal(
        nullptr) {
    m_Space = new int *[m_Height];
    for (int i = 0; i < m_Height; ++i) {
        m_Space[i] = new int[m_Width];
        for (int j = 0; j < m_Width; ++j) {
            m_Space[i][j] = 0;
        }
    }
    m_Hyenas = new int *[m_Height];
    for (int i = 0; i < m_Height; ++i) {
        m_Hyenas[i] = new int[m_Width];
        for (int j = 0; j < m_Width; ++j) {
            m_Hyenas[i][j] = 0;
        }
    }

    ///Местро для расстановки зверей
    m_Animal = new Animals *[MAX_ANIMALS];
    for (int i = 0; i < num_rabbits; ++i) {
        m_Animal[i] = new Rabbit(animals[i][0], animals[i][1], animals[i][2], animals[i][3], 0);
    }
    for (int i = 0; i < num_wolfs; ++i) {
        m_Animal[num_rabbits + i] = new Wolfs(animals[num_rabbits + i][0], animals[num_rabbits + i][1],
                                              animals[num_rabbits + i][2], animals[num_rabbits + i][3], 0);
    }
    for(int i = 0; i < num_hyenas; ++i){
        m_Animal[num_rabbits+num_wolfs+i] = new Hyenas(animals[num_rabbits+num_wolfs+i][0], animals[num_rabbits+num_wolfs+i][1],
                                                       animals[num_rabbits+num_wolfs+i][2], animals[num_rabbits+num_wolfs+i][3], 0);
    }
} ///Ready
void Simulator::Start(int steps){
    for(int i = 1; i <= steps; ++i){
        MoveAllAnimals(i); //Запускаем движение зверей
        ProcessNutrition(); //Процес питания
        AgingAllAnimals(); //Увеличиваем возраст выживши животных
        ProcessReproduce(i);
        ProcessDying();
//        PrintListAnimals();
        SetSpace();
//        PrintSpace();
        cout << i << "====" << endl;
        Print();
    }
    EnterSpace();

}
void Simulator::Print() const {
    for(int i = 0; i < m_Height; ++i){
        for(int j = 0; j < m_Width; ++j){
            int a = m_Space[i][j];
            int b = m_Hyenas[i][j];
            if(a == 0 && b == 0){
                cout << "#" ;
                continue;
            }
            if(b == 0){
                cout << a;
                continue;
            }
            if(a == 0){
                cout << "(" << b << ")";
                continue;
            }
            cout << a << "+(" << b << ")";
        }
        cout << endl;
    }
}
void Simulator::MoveAllAnimals(int step) const {
    for (int i = 0; i < m_CouAnimals; ++i) {
        if(m_Animal[i] == nullptr){
            continue;
        }
        m_Animal[i]->Move(m_Width, m_Height, step);
    }
}
void Simulator::ProcessNutrition() const {///??????????????????????????????????????????????????????????????
    for (int i = 0; i < m_CouAnimals; ++i) {
        if(m_Animal[i]->IsRabbit()) {
            int X_R = m_Animal[i]->GetX();
            int Y_R = m_Animal[i]->GetY();
            for (int j = 0; j < m_CouAnimals; ++j) {
                if (!m_Animal[j]->IsRabbit()) {
                    int X_W = m_Animal[j]->GetX();
                    int Y_W = m_Animal[j]->GetY();
                    if ((X_R == X_W) && (Y_R == Y_W)) {
                        int a = m_Animal[j]->GetCou();
                        m_Animal[j]->SetCou(a + 1);
                        while (i != m_CouAnimals-1) {
                            Animals *temp = m_Animal[i + 1];
                            m_Animal[i + 1] = m_Animal[i];
                            m_Animal[i] = temp;
                            i++;
                        }
                        m_CouAnimals = m_CouAnimals - 1;
                    }

                }
            }
        } //it's rabbit
        if(!m_Animal[i]->IsRabbit() && !m_Animal[i]->IsHyenas()){
            int X_R = m_Animal[i]->GetX();
            int Y_R = m_Animal[i]->GetY();
            for (int j = 0; j < m_CouAnimals; ++j) {
                if (m_Animal[j]->IsHyenas() && (m_Animal[j]->GetCou() < 2)) {
                    int X_W = m_Animal[j]->GetX();
                    int Y_W = m_Animal[j]->GetY();
                    if ((X_R == X_W) && (Y_R == Y_W)) {
                        int a = m_Animal[j]->GetCou();
                        m_Animal[j]->SetCou(a + 1);
                        while (i != m_CouAnimals-1) {
                            Animals *temp = m_Animal[i + 1];
                            m_Animal[i + 1] = m_Animal[i];
                            m_Animal[i] = temp;
                            i++;
                        }
                        m_CouAnimals = m_CouAnimals - 1;
                    }

                }
            }
        } // it's wolf
        if(m_Animal[i]-> IsHyenas()){
            int X_R = m_Animal[i]->GetX();
            int Y_R = m_Animal[i]->GetY();
            for (int j = i+1; j < m_CouAnimals; ++j) {
                if (m_Animal[j]->IsHyenas() && (m_Animal[j]->GetCou() < 2)) {
                    int X_W = m_Animal[j]->GetX();
                    int Y_W = m_Animal[j]->GetY();
                    if ((X_R == X_W) && (Y_R == Y_W)) {
                        int a = m_Animal[j]->GetCou();
                        m_Animal[j]->SetCou(a + 1);
                        while (i != m_CouAnimals-1) {
                            Animals *temp = m_Animal[i + 1];
                            m_Animal[i + 1] = m_Animal[i];
                            m_Animal[i] = temp;
                            i++;
                        }
                        m_CouAnimals = m_CouAnimals - 1;
                    }

                }
            }
        } //it's hyenas
    }
}
void Simulator::ProcessReproduce(int step){
    for(int i =0; i < m_CouAnimals; ++i){
        if(m_Animal[i]->CanReproduce()){
            AddNewAnimals(m_Animal[i]->GetX(), m_Animal[i]->GetY(), m_Animal[i]->GetDirection(), m_Animal[i]->GetConstancy(), m_Animal[i]->GetBirthStep(), step, m_Animal[i]);
            m_CouAnimals++;
            m_Animal[i]->SetCou(0);
        }
    }
}
void Simulator::AddNewAnimals(int x, int y, int dir, int constant, int birthStep, int step,  Animals* parent = nullptr) {
    if(parent->IsRabbit()){
        m_Animal[m_CouAnimals] = new Rabbit(x, y, dir, constant, step);
    }
    if(!parent->IsRabbit() && !parent->IsHyenas()){
        m_Animal[m_CouAnimals] = new Wolfs(x, y, dir, constant, step);
    }
    if(parent->IsHyenas()){
        m_Animal[m_CouAnimals] = new Hyenas(x, y, dir, constant, step);
    }
}
void Simulator::AgingAllAnimals() const {
    for (int i = 0; i < m_CouAnimals; ++i) {
        if(m_Animal[i] == nullptr){
            continue;
        }
        m_Animal[i]->Aging();
    }
}
void Simulator::ProcessDying() {
    for(int i = 0; i < m_CouAnimals; ++i){
        if (m_Animal[i] != nullptr) {
            if(((m_Animal[i]->IsRabbit() && m_Animal[i]->GetAge() == 10) ||
                (!m_Animal[i]->IsRabbit() && !m_Animal[i]->IsHyenas() && m_Animal[i]->GetAge() == 15)) ||
               (m_Animal[i]->IsHyenas() && m_Animal[i]->GetAge() == 15)){
                int j = i;
                while (j != m_CouAnimals-1) {
                    Animals *temp = m_Animal[j + 1];
                    m_Animal[j + 1] = m_Animal[j];
                    m_Animal[j] = temp;
                    j++;
                }
                m_CouAnimals = m_CouAnimals - 1;
                i = i - 1;
            }
        }
    }
}
void Simulator::SetSpace() {
    for (int j = 0; j < m_Height; ++j) {
        for (int k = 0; k < m_Width; ++k) {
            m_Space[j][k]=0;
            m_Hyenas[j][k] = 0;
        }
    }
    for (int i = 0; i < m_CouAnimals; ++i) {
        if(m_Animal[i] == nullptr){
            continue;
        }
        int X = m_Animal[i]->GetX(), Y = m_Animal[i]->GetY();
        if(m_Animal[i]->IsHyenas()){
            m_Hyenas[Y][X] = m_Hyenas[Y][X] +1;
            continue;
        }
        if(m_Animal[i]->IsRabbit()){
            m_Space[Y][X] = m_Space[Y][X] + 1;
            continue;
        }
        if(!(m_Animal[i]->IsRabbit())){
            m_Space[Y][X] = m_Space[Y][X] - 1;
        }
    }
}
Simulator::~Simulator(){
    for (int i = 0; i < m_CouAnimals; ++i) {
        delete m_Animal[i];
    }
    delete[] m_Animal;

    for (int i = 0; i < m_Height; ++i) {
        delete[] m_Space[i];
    }
    delete[] m_Space;
}
void Simulator::PrintSpace() {
    for (int j = 0; j < m_Width; ++j) {
        for (int k = 0; k < m_Height; ++k) {
            cout << m_Space[j][k];
        }
        cout << endl;
    }
}
void Simulator::PrintListAnimals() {
    for(int i = 0; i < m_CouAnimals; ++i){
        if(m_Animal[i] == nullptr){
            continue;
        }
        int x = m_Animal[i]->GetX();
        int y = m_Animal[i]->GetY();
        if(m_Animal[i]->IsRabbit()){
            cout << "(1&(" << x << ":" << y <<"))%" << m_Animal[i]->GetDirection() << " ";
            continue;
        }
        cout << "(-1&(" << x << ":" << y <<"))/"<< m_Animal[i]->GetDirection();
    }
}
void Simulator::EnterSpace() {
    ofstream Out("output.txt"); //открываем файл "output.txt"
    if (!Out.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }
    for(int i = 0; i < m_Height; ++i){
        for(int j = 0; j < m_Width; ++j){
            int a = m_Space[i][j];
            int b = m_Hyenas[i][j];
            if(a == 0 && b == 0){
                Out << "#" ;
                continue;
            }
            if(b == 0){
                Out << a;
                continue;
            }
            if(a == 0){
                Out << "(" << b << ")";
                continue;
            }
            if(a!=0 && b!=0){
                Out << a << "+(" << b << ")";
            }
        }
        Out << endl;
    }

}

int main() {
    system("chcp 65001"); // Русификация ввода/вывода
    ifstream F("input.txt"); //открываем файл "input.txt"
    if(!F){
        cout << "Не удалось открыть файл"<< endl;
        return 1;
    }
    int N, M, T, R, W, H;
    F >> N >> M >> T >> R >> W >> H;
    int** m_Arr = new int*[R+W+H];
    for(int i = 0; i < R+W+H; ++i){
        m_Arr[i] = new int[4];
        for(int j = 0; j < 4; ++j){
            F >> m_Arr[i][j];
        }
    }


    Simulator Sim(N, M, W, R, H, m_Arr);
    Sim.Start(T);



    //del
    for(int i = 0; i < R+W; ++i){
        delete[] m_Arr[i];
    }
    delete[] m_Arr;
    return 0;
}