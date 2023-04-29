#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Player {
    public:
        string name;
        string symble;
};

class Player1 : public Player {
    public:
        Player1() {
            this->symble = "x";
        }
};

class Player2 : public Player {
    public:
        Player2() {
            this->symble = "o";
        }
};

class Hash {
    private:
        int turns = 9;
        Player1 player1;
        Player2 player2;
        vector<vector<string>> table = {
            {"-", "-", "-"}, 
            {"-", "-", "-"}, 
            {"-", "-", "-"}
        };
        string pipe = "|";
        string blank = "-";
        string emptyStr = "";
        string spdEmptyStr = " ";
        /**
         * @brief Method to get the players' names from the terminal...
        */
        void askPlayersNames() 
        {
            cout << "Nome do player 1 (x): ";
            cin >> this->player1.name;

            cout << "Nome do player 2 (o): ";
            cin >> this->player2.name;
        }
        /**
         * @brief Method to show the Hash Game's table...
        */
        void showTable()
        {
            for(vector<vector<string>>::size_type i = 0; i != this->table.size(); i++) 
            {
                for(vector<string>::size_type j = 0; j != this->table[i].size(); j++)
                {
                    const string breaker = j != 2 ? this->pipe : this->emptyStr;

                    const string field = (this->table[i][j] == this->blank) 
                        ? to_string(i) + to_string(j) 
                        : this->table[i][j];

                    cout << field << breaker;
                }
                cout << endl;
            }
        }
        /**
         * @brief Method to get the string vector of table's positions...
        */
        vector<string> getTablePositions()
        {
            vector<string> positions;

            for(vector<vector<string>>::size_type i = 0; i != this->table.size(); i++) 
            {
                for(vector<string>::size_type j = 0; j != this->table[i].size(); j++)
                {
                    positions.push_back(to_string(i) + to_string(j));
                }
            }

            return positions;
        }
        /**
         * @brief Method to get the current player by the current game turn...
         * 
         * @return `player`.
        */
        Player getPlayer(int &turn) 
        {
            if (turn % 2 == 0 ) return this->player1;

            return this->player2;
        }
        /**
         * @brief Method to verify if the players' got position is a valid position on Hash Game's table...
        */
        bool verifyGotPositionIsValid(string &gotPosition)
        {
            return this->verifyGotPositionExists(gotPosition) && this->verifyGotPositionIsAvailable(gotPosition);
        }
        /**
         * @brief Method to convert the position from string to int vector...
        */
        vector<int> getPositionIndex(string &gotPosition)
        {
            vector<int> index;

            const int i = int(gotPosition.at(0)) - 48;

            const int j = int(gotPosition.at(1)) - 48;

            index.push_back(i);

            index.push_back(j);

            return index;
        }
        /**
         * @brief Method to verify if the players' got position is available on Hash Game's table...
        */
        bool verifyGotPositionIsAvailable(string &gotPosition)
        {
            vector<int> index = this->getPositionIndex(gotPosition);

            if (this->table[index[0]][index[1]] == this->blank) return true;

            return false;
        }
        /**
         * @brief Method to verify if the players' got position exists on Hash Game's table...
        */
        bool verifyGotPositionExists(string &gotPosition)
        {
            bool exists = false;

            vector<string> positions = this->getTablePositions();

            for(vector<string>::size_type i = 0; i != positions.size(); i++)
            {
                if(positions[i] == gotPosition) exists = true;
            }

            return exists;
        }
        /**
         * @brief Method to ask current player to choose a position on Hash Game's table...
        */
        vector<int> askPosition(Player &player)
        {
            string gotPosition;

            cout << "Escolha uma posição, " << player.name << " " << "(" << player.symble << "): ";

            cin >> gotPosition;

            if (this->verifyGotPositionIsValid(gotPosition)) 
                return this->getPositionIndex(gotPosition);

            cout << "Posição inválida!" << endl;

            return this->askPosition(player);
        }
        /**
         * @brief Method to insert the current player's symble into the Hash Game's table...
        */
        void insertPosition(Player &player, vector<int> &index) 
        {
            this->table[index[0]][index[1]] = player.symble + this->spdEmptyStr;
        }
        /**
         * @brief Method to verify if the current player is the winner...
        */
        bool verifyWinner(Player &player)
        {
            const string symble = player.symble + this->spdEmptyStr;

            bool lines = false;
            bool columns = false;
            bool mainDiagonal = true;
            bool secondaryDiagonal = true;

            for(vector<vector<string>>::size_type i = 0; i != this->table.size(); i++) 
            {
                bool line = true;
                bool column = true;

                for(vector<string>::size_type j = 0; j != this->table[i].size(); j++)
                {
                    if(this->table[i][j] != symble) line = false;
                    if(this->table[j][i] != symble) column = false;
                    if(i == j && this->table[i][j] != symble) mainDiagonal = false;
                    if(i + j == 2 && this->table[i][j] != symble) secondaryDiagonal = false;
                }

                if(line) {
                    lines = true;
                    break;
                }

                if(column) {
                    columns = true;
                    break;
                }
            }

            return lines || columns || mainDiagonal || secondaryDiagonal;
        }
    public:
        /**
         * @brief Method to start the Hash Game...
        */
        void start()
        {
            cout << "Jogo da Velha..." << endl;

            this->askPlayersNames();

            this->showTable();

            for(int turn = 0; turn < this->turns; turn++) {

                Player player = this->getPlayer(turn);

                vector<int> positionIndex = this->askPosition(player);

                this->insertPosition(player, positionIndex);

                this->showTable();

                if(this->verifyWinner(player)) {

                    cout << "O jogador " << player.name << " venceu!" << endl;

                    break;
                } else if(turn == this->turns - 1) {

                    cout << "Deu Velha!" << endl;
                }
            }
        }
        /**
         * @brief Method to stop the Hash Game deleting it from the memory...
        */
        void stop()
        {
            delete this;
        }
        ~Hash() {
            cout << "Fim de Jogo..." << endl;
        }
};

int main() 
{
    Hash* game = new Hash();
    game->start();
    game->stop();

    return 0;
}