#include<fstream>
#include<string>
#include<ctime>
#include<algorithm>
#include<random>
#include<cstdlib>
#include <chrono>
#include<msclr/marshal_cppstd.h>
using namespace System;
using namespace msclr::interop;
std::string toStandardString(String^ string)
{
    return marshal_as<std::string>(string);
}
String^ toSystemString(std::string str)
{
    return marshal_as<String^>(str);
}
/* User: ID, Name, Password, Role.*/
struct USER
{
	int ID;
    std::string Name;
    std::string Password;
    std::string Role;
};
/* Player: ID(number T-shirt), Name, birth date, nationality.*/
struct PLAYER
{
	int ID;
    std::string Name;
    int birth_date;
    std::string nationality;
};
/************************************************************/
/* Result: ID, TeamHomeGoals, TeamAwayGoals.*/
struct RESULT
{
    int ID;
    int TeamHomeGoals;
    int TeamAwayGoals;
}res[190];
/***************************************************/
/* Team: ID, Name, Players (array- 34).*/
struct TEAM
{
    std::string Name;
	int ID;
	PLAYER arr[34];
    std::string stadium;
    std::string Coach;
    int Founded;
}/*TEAMS*/
team_1, team_2, team_3, team_4, team_5, team_6, team_7, team_8,
team_9, team_10, team_11, team_12, team_13, team_14, team_15, team_16,
team_17, team_18, team_19, team_20;
/***************************************************/
/* TableRecord: ID, No, TeamName, Points.*/
struct TABLERECORD
{
    int ID = 1;
    std::string TeamName;
    int No;    int Points;    int match_played;     int Goal_Scored;  int Goal_Reseived;
};
/***************************************************/
/* Match: ID, TeamHome, TeamAway, StartDate, Result.*/
struct MATCH {
    int ID;
    std::string TeamHome;
    std::string TeamAway;
    std::string StartDate;
    RESULT result_match;
};
/***************************************************/
/* League: ID, Teams (array - 20), Matches (array - 190), Table (array - 20).*/
struct LEAGUE
{
	TEAM teams[20];
	int ID;
	TABLERECORD table[20];
    MATCH MaTch[190];
}myleague;
/**************************************************/
struct Cup
{
    MATCH MaTch_cup[16];
}Throo_Cup;
/***************************************************/
struct statis
{
    unsigned int Possession1, Possession2;
    unsigned int Shots1, Shots2;
    unsigned int Corners1, Corners2;
    unsigned int Fouls1, Fouls2;
    unsigned int Passes1, Passes2;
}statistics_of_match[10];
/***************************************************/
static int admin_no = 0;
static int user_no = 0;
USER arr_admin[50] = {};
USER arr_user[50] = {};
std::string teams_s[20] ={};
std::string saved_name, saved_password, saved_role;
int saved_id; int day[19] = {};	 static  int coco = 0;
bool save_data_login(USER Unknown, short no_of_type_user)
{
    bool repeated = false;
    switch (no_of_type_user)
    {
        // 1 ====> admin
    case(1):
    {
        for (int ch = 0; ch < admin_no; ch++)
        {
            if ((Unknown.Name == arr_admin[ch].Name) || (Unknown.Name == arr_user[ch].Name))
            {
                repeated = true;
                break;
            }
        }
        switch (repeated)
        {
        case(true):
        {
            return false;
            break;
        }
        case(false):
        {
            arr_admin[admin_no].Name = Unknown.Name;
            arr_admin[admin_no].ID = admin_no + 1;
            arr_admin[admin_no].Password = Unknown.Password;
            arr_admin[admin_no].Role = "Admin";
            saved_name = arr_admin[admin_no].Name;
            saved_password = arr_admin[admin_no].Password;
            saved_id = arr_admin[admin_no].ID;
            saved_role = arr_admin[admin_no].Role;
            //save data users in file
            std::ofstream outfile_admin("data_login.txt", std::ios::app);
            if (outfile_admin.is_open())
            {
                outfile_admin
                    <<arr_admin[admin_no].Name << "-" << arr_admin[admin_no].ID << "-" << arr_admin[admin_no].Password << "-" << arr_admin[admin_no].Role<<"-";
            }
            outfile_admin.close();
            admin_no++;
            return true;
            break;
        }
        }
        break;
    }
    // 2 ====> user
    repeated = false;
    case(2):
    {
        for (int ch = 0; ch < admin_no; ch++)
        {
            if ((Unknown.Name == arr_admin[ch].Name) || (Unknown.Name == arr_user[ch].Name))
            {
                repeated = true;
                break;
            }
        }
        switch (repeated)
        {
        case(true):
        {
            return false;
            break;
        }
        case(false):
        {
            //load data users from file
            saved_name = arr_user[user_no].Name = Unknown.Name;
            saved_id = arr_user[user_no].ID = user_no + 1;
            saved_password = arr_user[user_no].Password = Unknown.Password;
            arr_user[user_no].Role = "User";
            saved_role = arr_user[user_no].Role;
            //save data users in file
            std::ofstream outfile_user("data_login.txt", std::ios::app);
            if (outfile_user.is_open())
            {
                outfile_user
                    <<arr_user[user_no].Name << "-" << arr_user[user_no].ID << "-" << arr_user[user_no].Password << "-" << arr_user[user_no].Role<<"-";
            }
            outfile_user.close();
            user_no++;
            return true;
            break;
        }
        }
        break;
    }
    }
}
bool check_data_login(std::string name, std::string password, short no_type_of_user)
{
    switch (no_type_of_user)
    {
    case(1):
    {
        bool f_a = 0;
        for (int i = 0; i <= admin_no; i++)
        {
            if (name == arr_admin[i].Name && password == arr_admin[i].Password)
            {
                f_a = true;
                saved_name = arr_admin[i].Name;
                saved_password = arr_admin[i].Password;
                saved_id = arr_admin[i].ID;
                saved_role = arr_admin[i].Role;
                break;
            }
        }
        switch (f_a)
        {
        case true:
        {
            return f_a;
            break;
        }
        case false:
        {
            return f_a;
            break;
        }
        }
        break;
    }
    case(2):
    {
        bool f_u = 0;
        for (int i = 0; i <= user_no; i++)
        {
            if (name == arr_user[i].Name && password == arr_user[i].Password)
            {
                f_u = true;
                saved_name = arr_user[i].Name;
                saved_password = arr_user[i].Password;
                saved_id = arr_user[i].ID;
                saved_role = arr_user[i].Role;
                break;
            }
        }
        switch (f_u)
        {
        case true:
        {
            return f_u;
            break;
        }
        case false:
        {
            return f_u;
            break;
        }
        }
        break;
    }
    }
}
void update_data_of_players()
{
    std::ofstream data_ac_milan2("data_ac_milan.txt");
    std::ofstream data_ahly2("data_ahly.txt");
    std::ofstream data_ajax2("data_ajax.txt");
    std::ofstream data_arsenal2("data_arsenal.txt");
    std::ofstream data_barcelona2("data_barcelona.txt");
    std::ofstream data_atliteco2("data_atliteco.txt");
    std::ofstream data_benfica2("data_benfica.txt");
    std::ofstream data_bvb2("data_bvb.txt");
    std::ofstream data_byarn2("data_byarn.txt");
    std::ofstream data_chelsea2("data_chelsea.txt");
    std::ofstream data_inter_milan2("data_inter_milan.txt");
    std::ofstream data_juve2("data_juve.txt");
    std::ofstream data_liverpool2("data_liverpool.txt");
    std::ofstream data_man2("data_man.txt");
    std::ofstream data_man_united2("data_man_united.txt");
    std::ofstream data_napoli2("data_napoli.txt");
    std::ofstream data_psg2("data_psg.txt");
    std::ofstream data_roma2("data_roma.txt");
    std::ofstream data_real_madrid2("data_real_madrid.txt");
    std::ofstream data_tottenham2("data_tottenham.txt");
    int it = 0;
    for (; it < 34; it++)
    {
        data_ac_milan2 << team_1.arr[it].Name << "-" << team_1.arr[it].ID << "-" << team_1.arr[it].birth_date << "-" << team_1.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_ahly2 << team_2.arr[it].Name << "-" << team_2.arr[it].ID << "-" << team_2.arr[it].birth_date << "-" << team_2.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_ajax2 << team_3.arr[it].Name << "-" << team_3.arr[it].ID << "-" << team_3.arr[it].birth_date << "-" << team_3.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_arsenal2 << team_4.arr[it].Name << "-" << team_4.arr[it].ID << "-" << team_4.arr[it].birth_date << "-" << team_4.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_barcelona2 << team_5.arr[it].Name << "-" << team_5.arr[it].ID << "-" << team_5.arr[it].birth_date << "-" << team_5.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_atliteco2 << team_6.arr[it].Name << "-" << team_6.arr[it].ID << "-" << team_6.arr[it].birth_date << "-" << team_6.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_benfica2 << team_7.arr[it].Name << "-" << team_7.arr[it].ID << "-" << team_7.arr[it].birth_date << "-" << team_7.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_bvb2 << team_8.arr[it].Name << "-" << team_8.arr[it].ID << "-" << team_8.arr[it].birth_date << "-" << team_8.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_byarn2 << team_9.arr[it].Name << "-" << team_9.arr[it].ID << "-" << team_9.arr[it].birth_date << "-" << team_9.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_chelsea2 << team_10.arr[it].Name << "-" << team_10.arr[it].ID << "-" << team_10.arr[it].birth_date << "-" << team_10.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_inter_milan2 << team_11.arr[it].Name << "-" << team_11.arr[it].ID << "-" << team_11.arr[it].birth_date << "-" << team_11.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_juve2 << team_12.arr[it].Name << "-" << team_12.arr[it].ID << "-" << team_12.arr[it].birth_date << "-" << team_12.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_liverpool2 << team_13.arr[it].Name << "-" << team_13.arr[it].ID << "-" << team_13.arr[it].birth_date << "-" << team_13.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_man2 << team_14.arr[it].Name << "-" << team_14.arr[it].ID << "-" << team_14.arr[it].birth_date << "-" << team_14.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_man_united2 << team_15.arr[it].Name << "-" << team_15.arr[it].ID << "-" << team_15.arr[it].birth_date << "-" << team_15.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_napoli2 << team_16.arr[it].Name << "-" << team_16.arr[it].ID << "-" << team_16.arr[it].birth_date << "-" << team_16.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_psg2 << team_17.arr[it].Name << "-" << team_17.arr[it].ID << "-" << team_17.arr[it].birth_date << "-" << team_17.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_roma2 << team_18.arr[it].Name << "-" << team_18.arr[it].ID << "-" << team_18.arr[it].birth_date << "-" << team_18.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_real_madrid2 << team_19.arr[it].Name << "-" << team_19.arr[it].ID << "-" << team_19.arr[it].birth_date << "-" << team_19.arr[it].nationality << "-";
    } for (it = 0; it < 34; it++)
    {
        data_tottenham2 << team_20.arr[it].Name << "-" << team_20.arr[it].ID << "-" << team_20.arr[it].birth_date << "-" << team_20.arr[it].nationality << "-";
    } 
}
void add_teams_to_program()
{
    std::ifstream data_ac_milan("data_ac_milan.txt");
    std::ifstream data_ahly("data_ahly.txt");
    std::ifstream data_ajax("data_ajax.txt");
    std::ifstream data_arsenal("data_arsenal.txt");
    std::ifstream data_barcelona("data_barcelona.txt");
    std::ifstream data_atliteco("data_atliteco.txt");
    std::ifstream data_benfica("data_benfica.txt");
    std::ifstream data_bvb("data_bvb.txt");
    std::ifstream data_byarn("data_byarn.txt");
    std::ifstream data_chelsea("data_chelsea.txt");
    std::ifstream data_inter_milan("data_inter_milan.txt");
    std::ifstream data_juve("data_juve.txt");
    std::ifstream data_liverpool("data_liverpool.txt");
    std::ifstream data_man("data_man.txt");
    std::ifstream data_man_united("data_man_united.txt");
    std::ifstream data_napoli("data_napoli.txt");
    std::ifstream data_psg("data_psg.txt");
    std::ifstream data_roma("data_roma.txt");
    std::ifstream data_real_madrid("data_real_madrid.txt");
    std::ifstream data_tottenham("data_tottenham.txt");

        //add_acmilan
        team_1.Name = "AC Milan";
        team_1.ID = 1;
        team_1.stadium = "San Siro";
        team_1.Founded = 1889;
        team_1.Coach = "Stefano pioli";
        std::string line;
        std::getline(data_ac_milan, line);
        short i = 0;
        size_t pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_1.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_1.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_1.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_1.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
      
        //add_ahly
        team_2.Name = "Al Ahly";
        team_2.ID = 2;
        team_2.stadium = "Cairo International Stadium";
        team_2.Founded = 1907;
        team_2.Coach = "marcel kollar";
        line="";
        std::getline(data_ahly, line);
         i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_2.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_2.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_2.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_2.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
      
        //add_ajax
        team_3.Name = "Ajax";
        team_3.ID = 3;
        team_3.stadium = " Orange Vélodrome";
        team_3.Founded = 1900;
        team_3.Coach = "john Hettinga";
        line = "";
        std::getline(data_ajax, line);
         i = 0;
         pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_3.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_3.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_3.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_3.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
      
        //add arsenal
        team_4.Name = "Arsenal";
        team_4.ID = 4;
        team_4.stadium = "Emirates Stadium";
        team_4.Founded = 1886;
        team_4.Coach = "john Hettinga";
        line = "";
        std::getline(data_arsenal, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_4.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_4.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_4.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_4.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }

        //add_atleletico_madrid
        team_5.Name = "Atletico de Madrid";
        team_5.ID = 5;
        team_5.stadium = "Wanda Metropolitano";
        team_5.Founded = 1903;
        team_5.Coach = "Diego simeone";
        line = "";
        std::getline(data_atliteco, line);
        i = 0;
         pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_5.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_5.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_5.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_5.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
     
        //add_barcelona
        team_6.Name = "Barcelona";
        team_6.ID = 6;
        team_6.stadium = " Camp Nou";
        team_6.Founded = 1899;
        team_6.Coach = "xavi";
        line = "";
        std::getline(data_barcelona, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_6.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_6.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_6.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_6.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }

        //add_benfica
        team_7.Name = "Benfica";
        team_7.ID = 7;
        team_7.stadium = "Estádio da Luz";
        team_7.Founded = 1904;
        team_7.Coach = "Rogers schmidt";
        line = "";
        std::getline(data_benfica, line);
         i = 0;
         pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_7.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_7.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_7.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_7.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
    
        //add_bvb
        team_8.Name = "Borussia Dortmund";
        team_8.ID = 8;
        team_8.stadium = "Signal Iduna Park";
        team_8.Founded = 1909;
        team_8.Coach = "Aiden's terezik";
        line = "";
        std::getline(data_bvb, line);
         i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_8.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_8.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_8.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_8.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
        
        //add_byarn
        team_9.Name = "Bayern Munich";
        team_9.ID = 9;
        team_9.stadium = " Alianz Arena";
        team_9.Founded = 1900;
        team_9.Coach = "Thomas tuchel";
        line = "";
        std::getline(data_byarn, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_9.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_9.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_9.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_9.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
      
        //add_chelsea
        team_10.Name = "Chelsea";
        team_10.ID = 10;
        team_10.stadium = "Stamford Bridge";
        team_10.Founded = 1905;
        team_10.Coach = "Frank Lampard";
        line = "";
        std::getline(data_chelsea, line);
        i = 0;
       pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_10.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_10.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_10.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_10.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }

        //add_inter_milan
        team_11.Name = "Inter Milan";
        team_11.ID = 11;
        team_11.stadium = "San Siro";
        team_11.Founded = 1908;
        team_11.Coach = "inzaghi";
        line = "";
        std::getline(data_inter_milan, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_11.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_11.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_11.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_11.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
       
        //add_juventus
        team_12.Name = "Juventus";
        team_12.ID = 12;
        team_12.stadium = "Allianz Stadium";
        team_12.Founded = 1897;
        team_12.Coach = "allegri";
        line = "";
        std::getline(data_juve, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_12.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_12.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_12.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_12.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
     
        //add_liverpool
        team_13.Name = "Liverpool";
        team_13.ID = 13;
        team_13.stadium = "Anfield";
        team_13.Founded = 1892;
        team_13.Coach = "Jurgen klopp";
        line = "";
        std::getline(data_liverpool, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_13.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_13.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_13.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_13.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
 
        //add_man
        team_14.Name = "Manchester City";
        team_14.ID = 14;
        team_14.stadium = "Etihad Stadium";
        team_14.Founded = 1880;
        team_14.Coach = "beb Guardiola";
        line = "";
        std::getline(data_man, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_14.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_14.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_14.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_14.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }

        //add_man_united
        team_15.Name = "Manchester United";
        team_15.ID = 15;
        team_15.stadium = " Old Trafford";
        team_15.Founded = 1878;
        team_15.Coach = "ten heg";
        line = "";
        std::getline(data_man_united, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_15.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_15.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_15.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_15.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
       


        //add_napoli
        team_16.Name = "Napoli";
        team_16.ID = 16;
        team_16.stadium = "Stadio San Paolo";
        team_16.Founded = 1926;
        team_16.Coach = "Luciano spalletti";
        line = "";
        std::getline(data_napoli, line);
        i = 0;
         pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_16.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_16.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_16.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_16.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
       

        //add_psg
        team_17.Name = "Paris Saint Germain";
        team_17.ID = 17;
        team_17.stadium = "Parc des Princes";
        team_17.Founded = 1970;
        team_17.Coach = "Christophe Galtier";
        line = "";
        std::getline(data_psg, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_17.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_17.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_17.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_17.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
      

        //add_real_madrid
        team_18.Name = "Real Madrid";
        team_18.ID = 18;
        team_18.stadium = "Santiago Bernabéu";
        team_18.Founded = 1902;
        team_18.Coach = "carlo Ancelotti";
        line = "";
        std::getline(data_real_madrid, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_18.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_18.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_18.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_18.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
      

        //add_roma
        team_19.Name = "Roma";
        team_19.ID = 19;
        team_19.stadium = "Stadio Olimpico";
        team_19.Founded = 1927;
        team_19.Coach = "Jose Mourinho";
        line = "";
        std::getline(data_roma, line);
         i = 0;
         pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_19.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_19.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_19.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_19.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
       
        //add_tottenham
        team_20.Name = "Tottenham Hotspur";
        team_20.ID = 20;
        team_20.stadium = "Tottenham Hotspur Stadium";
        team_20.Founded = 1882;
        team_20.Coach = "conte";
        line = "";
        std::getline(data_tottenham, line);
        i = 0;
        pos = 0;
        while (i < 34)
        {
            pos = line.find("-");
            team_20.arr[i].Name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_20.arr[i].ID = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_20.arr[i].birth_date = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find("-");
            team_20.arr[i].nationality = line.substr(0, pos);
            line.erase(0, pos + 1);
            i++;
        }
}
void generate_schedule(std::string teams[])
{
    myleague.ID = 1;
    std::srand(std::time(nullptr));
    int team_idx[20] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
    std::shuffle(team_idx, team_idx + 20, std::default_random_engine((rand()%(50-10+1)+10)));
    int coun = 0;
    for (int w = 0; w < 19; w++)
    {
        for (int g = 0; g < 10; g++)
        {
            int team1_idx = team_idx[(g + w) % 20], team2_idx = team_idx[(20 - 1 - g + w) % 20];
            std::string team1 = teams[team1_idx], team2 = teams[team2_idx];
            if (w % 2 == 0)
            {
                myleague.MaTch[coun].TeamHome = team1;
                myleague.MaTch[coun].TeamAway = team2;
                myleague.MaTch[coun].ID = coun + 1;
            }
            else
            {
                myleague.MaTch[coun].TeamHome = team2;
                myleague.MaTch[coun].TeamAway = team1;
                myleague.MaTch[coun].ID = coun + 1;
            }
            coun++;
        }
    }
}
/******************************************/
void generate_table(int indx_start)
{
    for (int c = indx_start; c < indx_start+10; c++)
    {
        for (int counter = 0; counter < 20; counter++)
        {
            if (myleague.table[counter].TeamName == myleague.MaTch[c].TeamHome)
            {
                myleague.table[counter].match_played += 1;
                if (myleague.MaTch[c].result_match.TeamHomeGoals > myleague.MaTch[c].result_match.TeamAwayGoals)
                    myleague.table[counter].Points += 3;
                else if (myleague.MaTch[c].result_match.TeamHomeGoals == myleague.MaTch[c].result_match.TeamAwayGoals)
                    myleague.table[counter].Points += 1;
                myleague.table[counter].Goal_Scored += myleague.MaTch[c].result_match.TeamHomeGoals;
                myleague.table[counter].Goal_Reseived+= myleague.MaTch[c].result_match.TeamAwayGoals;
            }
            if (myleague.table[counter].TeamName == myleague.MaTch[c].TeamAway)
            {
                myleague.table[counter].match_played += 1;
                if (myleague.MaTch[c].result_match.TeamAwayGoals > myleague.MaTch[c].result_match.TeamHomeGoals)
                    myleague.table[counter].Points += 3;
                else if (myleague.MaTch[c].result_match.TeamAwayGoals == myleague.MaTch[c].result_match.TeamHomeGoals)
                    myleague.table[counter].Points += 1;
                myleague.table[counter].Goal_Scored += myleague.MaTch[c].result_match.TeamAwayGoals;
                myleague.table[counter].Goal_Reseived += myleague.MaTch[c].result_match.TeamHomeGoals;
            }
        }
        if (c == 0)
        {
            int xs = 0;
            for (int yyy = 0; yyy < 8; yyy++)
            {
                Throo_Cup.MaTch_cup[yyy].TeamHome = myleague.table[xs].TeamName;
                Throo_Cup.MaTch_cup[yyy].TeamAway = myleague.table[xs+1].TeamName;
                Throo_Cup.MaTch_cup[yyy].ID = yyy + 1;
                xs += 2;
            }
        }
    }
}
bool sort_table_helper(const TABLERECORD& sample_1, const TABLERECORD& sample_2) {
    if (sample_1.Points != sample_2.Points)
        return sample_1.Points > sample_2.Points;
    else
        return (sample_1.Goal_Scored- sample_1.Goal_Reseived) > (sample_2.Goal_Scored - sample_2.Goal_Reseived);
}
void sort_table()
{
    std::sort(myleague.table, myleague.table + 20, sort_table_helper);
}
/***************************************************************************************/
int count_rounds, i , i2 ;
void logout_process()
{
    std::ofstream logout("load_data.txt");
    if (logout.is_open())
    {
        logout << count_rounds << "-" << day[0];
        int inc = 7;
        for (int da = 1; da < 19; da++)
        {
            day[da] = day[0] + inc;
            if (day[da] > 30)
            {
                day[da] -= 30;
                logout << "-" << day[da];
            }
            else
            {
                logout << "-" << day[da];
            }
            inc += 7;
        }
        for (int p = 0; p < 20; p++)
        {//table 
            logout << "-" << myleague.table[p].TeamName << "-"
                << myleague.table[p].match_played << "-"
                << myleague.table[p].Points << "-"
                << myleague.table[p].Goal_Scored << "-"
                << myleague.table[p].Goal_Reseived;
        }
        i = 0;
        for (int p = 0; p < 16; p++)
        {//table 
            if (p == 15)
            {
                logout << "-" << Throo_Cup.MaTch_cup[p].TeamHome;
                break;
            }
            logout << "-" <<Throo_Cup.MaTch_cup[p].TeamHome << "-"
                << Throo_Cup.MaTch_cup[p].TeamAway << "-"
                << Throo_Cup.MaTch_cup[p].result_match.TeamHomeGoals << "-"
                << Throo_Cup.MaTch_cup[p].result_match.TeamAwayGoals;
        }
        i = 0;
        for (; i < 190; i++)
        {
            logout << "-" << myleague.MaTch[i].TeamHome << "-"
                << myleague.MaTch[i].TeamAway;
        }
        i = 0;
        for (; i < 190; i++) {
            logout << "-" << myleague.MaTch[i].result_match.TeamHomeGoals << "-"
                << myleague.MaTch[i].result_match.TeamAwayGoals;
        }
    }
    logout.close();
}

int counter_of_weeks;
int login_process()
{
    std::ifstream login("load_data.txt");
    if (login.peek() == std::ifstream::traits_type::eof())
    {
        return 0;
    }
    else 
    {
        std::string data;
        getline(login, data);
        size_t pos;
        pos = data.find("-");
        counter_of_weeks = count_rounds = std::stoi(data.substr(0, pos));
        data.erase(0, pos + 1);
        pos = data.find("-");
        day[0] = std::stoi(data.substr(0, pos));
        data.erase(0, pos + 1);
        for (int da_d = 1; da_d < 19; da_d++)
        {
            pos = data.find("-");
            day[da_d] = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
        }
        add_teams_to_program();
        int count_t = 0;
        while (count_t < 20)
        {
            pos = data.find("-");
            myleague.table[count_t].TeamName = data.substr(0, pos);
            data.erase(0, pos + 1);
            pos = data.find("-");
            myleague.table[count_t].match_played = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            pos = data.find("-");
            myleague.table[count_t].Points = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            pos = data.find("-");
            myleague.table[count_t].Goal_Scored = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            pos = data.find("-");
            myleague.table[count_t].Goal_Reseived = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            count_t++;
        }
        count_t = 0;
        while (count_t < 16)
        {
            if (count_t == 15)
            {
                pos = data.find("-");
                Throo_Cup.MaTch_cup[count_t].TeamHome = data.substr(0, pos);
                data.erase(0, pos + 1);
                break;
            }
            pos = data.find("-");
            Throo_Cup.MaTch_cup[count_t].TeamHome = data.substr(0, pos);
            data.erase(0, pos + 1);
            pos = data.find("-");
            Throo_Cup.MaTch_cup[count_t].TeamAway = data.substr(0, pos);
            data.erase(0, pos + 1);
            pos = data.find("-");
            Throo_Cup.MaTch_cup[count_t].result_match.TeamHomeGoals = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            pos = data.find("-");
            Throo_Cup.MaTch_cup[count_t].result_match.TeamAwayGoals = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            count_t++;
        }
        count_t = 0;
        while (count_t < 190)
        {
            pos = data.find("-");
            myleague.MaTch[count_t].TeamHome = data.substr(0, pos);
            data.erase(0, pos + 1);
            pos = data.find("-");
            myleague.MaTch[count_t].TeamAway = data.substr(0, pos);
            data.erase(0, pos + 1);
            count_t++;
        }
        i2 = 0;
        while (i2 < 190)
        {
            pos = data.find("-");
            myleague.MaTch[i2].result_match.TeamHomeGoals = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            pos = data.find("-");
            myleague.MaTch[i2].result_match.TeamAwayGoals = std::stoi(data.substr(0, pos));
            data.erase(0, pos + 1);
            i2++;
        }
        return 1;
    }
    login.close();
}
void load_data_login_program()
{
    std::ifstream login_user("data_login.txt", std::ios::app);
    std::string line_login;
    std::getline(login_user, line_login);
    size_t pos = 0;
    USER sample[50]; int u = 0;
    while (line_login!="")
    {
        pos = line_login.find("-");
        sample[u].Name = line_login.substr(0, pos);
        line_login.erase(0, pos + 1);
        pos = line_login.find("-");
        sample[u].ID = std::stoi(line_login.substr(0, pos));
        line_login.erase(0, pos + 1);
        pos = line_login.find("-");
        sample[u].Password = line_login.substr(0, pos);
        line_login.erase(0, pos + 1);
        pos = line_login.find("-");
        sample[u].Role = line_login.substr(0, pos);
        line_login.erase(0, pos + 1);
        if (sample[u].Role == "Admin")
        {
            arr_admin[admin_no] = sample[u];
            admin_no++;
        }
        else
        {
            arr_user[user_no] = sample[u];
            user_no++;
        }
        u++;
    }
}
int random_results()
{
    return rand() % (6 - 0 + 1) + 0;
}
void statistics(int n)
{
    std::srand(std::time(nullptr));
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> distribution(50.0, 10.0); // mean = 50, standard deviation = 10
    for (int il = n; il < n+10; il++)
    {
        statistics_of_match[il].Possession1 = static_cast<int>(distribution(generator) + 0.5);
        if (statistics_of_match[il].Possession1 > 100) {
            statistics_of_match[il].Possession1 = 100;
        }
        else if (statistics_of_match[il].Possession1 < 0) {
            statistics_of_match[il].Possession1 = 0;
        }
        statistics_of_match[il].Possession2 = 100 - statistics_of_match[il].Possession1;
        statistics_of_match[il].Passes1 = rand() % (800 - 300 + 1) + 300;
        statistics_of_match[il].Passes2 = rand() % (800 - 300 + 1) + 300;
        statistics_of_match[il].Shots1 = rand() % 25;
        statistics_of_match[il].Shots2 = rand() % 25;
        statistics_of_match[il].Corners1 = rand() % 18;
        statistics_of_match[il].Corners2 = rand() % 18;
        statistics_of_match[il].Fouls1 = rand() % (25 - 10 + 1) + 10;
        statistics_of_match[il].Fouls2 = rand() % (25 - 10 + 1) + 10;
    }
}
void date_of_match(int* arr, int date_of_start) {
    for (int i = 0; i < 19; i++) {
        if (date_of_start > 30) {
            date_of_start -= 30;
        }
        arr[i] = date_of_start;
        date_of_start += 7;
    }
}