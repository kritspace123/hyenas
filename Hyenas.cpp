class Simulator {
private:
    int m_Width , m_Height; //x, y
    int** m_Space;
    Animals** m_Animal;
    mutable int m_CouAnimals;
public:
//    Simulator(int width, int height, int num_wolfs, int num_rabbits, int num_hyenas, int** animals);
    void Start(int steps);
    void Print() const;///Непотно как
//    void MoveAllAnimals(int step) const;
//    void ProcessNutrition() const;
//    void ProcessReproduce(int step);
//    void AgingAllAnimals() const;
//    void AddNewAnimals(int x, int y, int dir, int constant, int birthStep,int step, Animals* parent);
//    void ProcessDying();
    void SetSpace();
    void PrintSpace();
    void EnterSpace(){
        ofstream Out("output.txt"); //открываем файл "output.txt"
        if (!Out.is_open()) {
            std::cerr << "Ошибка открытия файла!" << std::endl;
            return;
        }
        for(int i = 0; i < m_Height; ++i){
            for(int j = 0; j < m_Width; ++j){
                int a = m_Space[i][j];
                if(a == 0){
                    Out << "#" ;
                } else{
                    Out << a;
                }

            }
            Out << endl;
        }

    }
    ~Simulator();

};