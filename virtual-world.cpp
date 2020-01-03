#include <iostream>
#include <chrono>
#include <vector>
#include "modules/generate_vector.cpp"
#include "modules/random_name.cpp"
#include "modules/random_job.cpp"
#include <ctime>
#include <thread>
#include <fstream>

class Subject{
  public:
    std::string Name = random_name(); //
    std::string Work = random_job();  //
    int Salary;
    int Wallet;
    int Happiness;
    int Age;                          //
    int Job_Level;                    //
    int Lifetime_Earnings = 0;        //
    int Energy;
    std::vector<std::string> Illnesses;
};

class Entertainment{
  public:
    std::vector<std::string> places = generate_vector("dataset/entertainment/places.txt");
    std::vector<int> effect = generate_vector_temp1();
    std::vector<int> price = generate_vector_temp2();
};

int get_salary(int wallet, int salary){
    wallet = wallet + salary;
    return wallet;
}
int reduce_happiness(int happiness){
    happiness = happiness - 10;
    return happiness;
}
int go_entertaining_wallet;
int return_entertaining_wallet(int Wallet, int price){
    go_entertaining_wallet = Wallet - price;
}
int go_entertaining(int Wallet, int Happiness, std::vector<std::string> places,
  std::vector<int> effect, std::vector<int> price){
    srand( time( 0 ) );
    int entertainment_choice = rand()% places.size();
    if(price[entertainment_choice]>Wallet){
      while(price[entertainment_choice]>Wallet){
        srand( time( 0 ) );
        entertainment_choice = rand()% places.size();
      }
    }
    std::cout << "\nSubject decided to go: " << places[entertainment_choice];
    Happiness = Happiness + effect[entertainment_choice];
    return_entertaining_wallet(Wallet, price[entertainment_choice]);
    return Happiness;
}
int check_promotion_salary = 50;
int check_promotion(int job_level){
    srand( time( 0 ) );
    int promotion_probability = rand()% 100;
    if(promotion_probability<50){
      std::cout << "\nSubject was promoted";
      job_level = job_level + 1;
      check_promotion_salary = check_promotion_salary + 50;
    }
    return job_level;
}
int reduce_energy(int energy){
    energy = energy - 5;
    return energy;
}

int main(){
  std::cout << "Starting the simulation...";
  Subject subject1;
  std::cout << "\nCreated subject: " << subject1.Name;
  std::cout << "\nAssigned job: " << subject1.Work;
  bool unemployed = false;
  subject1.Salary = 50;
  std::cout << "\nSubject salary: " << subject1.Salary;
  subject1.Wallet = 0;
  std::cout << "\nCreated " << subject1.Name << " wallet";
  subject1.Happiness = 100;
  subject1.Age = 18;
  Entertainment subject1_entertainment;
  subject1.Job_Level = 1;
  subject1.Energy = 100;

  bool ongoing_simulation = true;
  int day = 0; int month = 0; int year = 0;

  srand( time(0));
  for(int i = 0; i < 10; i++){
    while(ongoing_simulation == true){
      printf("\033c");
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));

      if(subject1.Happiness < 30){
        subject1.Happiness = go_entertaining(subject1.Wallet, subject1.Happiness, subject1_entertainment.places,
        subject1_entertainment.effect, subject1_entertainment.price);
        subject1.Wallet = go_entertaining_wallet;
      }

      if(subject1.Happiness < 1){
        std::cout << "\nThe subject commited suicide due to depression";
        ongoing_simulation = false;
      }
      day++;
      if(day==30){
        month++;
        day = 0;
        if(subject1.Job_Level < 10){
          subject1.Job_Level = check_promotion(subject1.Job_Level);
          subject1.Salary = check_promotion_salary;
        }
      }
      else if(month==12){
        month = 0;
        year++;
        subject1.Age++;
        if(subject1.Illnesses.size()>0){
          srand(time(0));
          int prob = rand()%100;
          int probability_rate = 30;
          if(prob<probability_rate){
            ongoing_simulation=false;
            std::cout << "\nSubject died from cancer";
          }
        }
        if(subject1.Illnesses.size() == 0){
          srand(time(0));
          int prob = rand()%100;
          int probability_rate = 3;
          if(prob<probability_rate){
            subject1.Illnesses.push_back("Cancer");
            std::cout << "\nUnfortunately, the subject was diagnosed with cancer";
          }
        }
      }
      if(subject1.Age==100){
        ongoing_simulation=false;
        std::cout << "\n\nLifetime earnings: " << subject1.Lifetime_Earnings << "$";
      }
      if(subject1.Age > 50&&unemployed==false){
        srand( time( 0 ) );
        int choice = rand()%10;
        if(choice < 2){
          unemployed == true;
          subject1.Work = "Retired";
          subject1.Salary = subject1.Salary / 2;
        }
      }
      if(subject1.Age > 50){
        srand(time(0));
        int prob = rand()%100;
        int probability_rate = subject1.Age - 50;
        if(prob<probability_rate){
          ongoing_simulation=false;
          std::cout << "\nThe subject died";
        }
      }

      std::string test_var;
      std::cout << "\n\n[Name]:        " << subject1.Name;
      std::cout << "\n[Age]:         " << subject1.Age;
      std::cout << "\n[Money]:       " << subject1.Wallet << "$";
      std::cout << "\n[Job]:         " << subject1.Work << " " << subject1.Job_Level;
      std::cout << "\n[Happiness]:   [" << subject1.Happiness << "/100]";
      std::cout << "\n[Energy]:      [" << subject1.Energy << "/100]";
      if(subject1.Illnesses.size()>0){
        std::cout << "\n[Illnesses]:   " << subject1.Illnesses[0];
      }
      std::cout << "\n\nDay: " << day << "; Month: " << month << "; Year: " << year << ";\n";
      //std::cout << "\n[s] to skip the day\n";
      //std::cin >> test_var;

      subject1.Wallet = get_salary(subject1.Wallet, subject1.Salary);
      subject1.Lifetime_Earnings = get_salary(subject1.Wallet, subject1.Salary);
      subject1.Happiness = reduce_happiness(subject1.Happiness);
      subject1.Energy = reduce_energy(subject1.Energy);
      subject1.Energy = subject1.Energy + 5;

    }
    //std::ofstream outfile ("dataset.csv");
    //outfile.close();

    // file pointer
    std::fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("dataset.csv", std::ios::out | std::ios::app);
    fout << subject1.Name << ", " << subject1.Age << ", " << subject1.Work
         << ", " << subject1.Job_Level << ", " << subject1.Lifetime_Earnings
         << "\n";
    }
}
