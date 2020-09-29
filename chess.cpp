#include "chess.h"
#include <time.h>
#include <stdlib.h>
#define M 100; // 棋盘边缘空隙
chess::chess()
{
}
// 统计玩家或者电脑连成的子
int personN = 0; // 玩家连成子的个数
int AIN = 0; // AI连成子的个数
int empty = 0; // 各方向空白位的个数
// 统计玩家或者电脑连成的子

void chess::start(Type type)
{
    gameType = type;
    // 初始棋盘
    mapGV.clear();
    player=true;
    clear();
    // 如果是AI模式，需要初始化评分数组
    if (gameType == AI)
    {
        mapSV.clear();
        clear();
    }
}
void chess::clear(){
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> line;
        for (int j = 0; j < 20; j++)
            line.push_back(0);
        mapGV.push_back(line);
    }
}

void chess::updateMap(int row, int col)
{
    if (player) mapGV[row][col] = 1;
    else mapGV[row][col] = -1;
    // 换手
    player = !player;
}

bool chess::isDead()//判断和棋

{
    // 所有空格全部填满
    for (int i = 1; i < 20; i++)
        for (int j = 1; j < 20; j++)
        {
            if (!(mapGV[i][j] == -1 || mapGV[i][j] == 1))
                return false;
        }
    return true;
}

bool chess::winorlose(int row, int col)
{
    // 横竖斜四种大情况
    // 水平方向
    for (int i = 0; i < 6; i++)
    {
        // 往左6个，往右匹配5个子，20种情况
        if (col - i > 0 &&col - i + 5 < 20 &&
            mapGV[row][col - i] == mapGV[row][col - i + 1] &&mapGV[row][col - i] == mapGV[row][col - i + 2] &&mapGV[row][col - i] == mapGV[row][col - i + 3] &&mapGV[row][col - i] == mapGV[row][col - i + 4] &&mapGV[row][col - i] == mapGV[row][col - i + 5])
            return true;
    }

    // 竖直方向
    for (int i = 0; i < 6; i++)
    {
        if (row - i > 0 &&row - i + 5 < 20 &&
            mapGV[row - i][col] == mapGV[row - i + 1][col] &&mapGV[row - i][col] == mapGV[row - i + 2][col] &&mapGV[row - i][col] == mapGV[row - i + 3][col] &&mapGV[row - i][col] == mapGV[row - i + 4][col] &&mapGV[row - i][col] == mapGV[row - i + 5][col])
            return true;
    }

    // 左斜方向
    for (int i = 0; i < 6; i++)
    {
        if (row + i < 20 &&row + i - 5 > 0 &&col - i > 0 &&col - i +5 < 20 &&
            mapGV[row + i][col - i] == mapGV[row + i - 1][col - i + 1] &&mapGV[row + i][col - i] == mapGV[row + i - 2][col - i + 2] &&mapGV[row + i][col - i] == mapGV[row + i - 3][col - i + 3] &&mapGV[row + i][col - i] == mapGV[row + i - 4][col - i + 4] &&mapGV[row + i][col - i] == mapGV[row + i - 5][col - i + 5])
            return true;
    }

    // 右斜方向
    for (int i = 0; i < 6; i++)
    {
        if (row - i > 0 &&row - i + 5 < 20 &&col - i > 0 &&col - i + 5 < 20 &&
            mapGV[row - i][col - i] == mapGV[row - i + 1][col - i + 1] &&mapGV[row - i][col - i] == mapGV[row - i + 2][col - i + 2] &&mapGV[row - i][col - i] == mapGV[row - i + 3][col - i + 3] &&mapGV[row - i][col - i] == mapGV[row - i + 4][col - i + 4] &&mapGV[row - i][col - i] == mapGV[row - i + 5][col - i + 5])

            return true;
    }
    return false;
}
//禁手
bool chess::isFour(int row, int col){
    int num=0,num1=0,num2=0,num3=0;
    for (int i = 0; i < 4; i++)
    {

        if (col - i > 0 &&col - i + 3 < 20 &&
            mapGV[row][col - i] == mapGV[row][col - i + 1] &&mapGV[row][col - i] == mapGV[row][col - i + 2] &&mapGV[row][col - i] == mapGV[row][col - i + 3]&&mapGV[row][col - i + 4]!=-1 )
            num=1;
    }

    // 竖直方向(上下延伸5个)
    for (int i = 0; i < 4; i++)
    {
        if (row - i > 0 &&row - i + 3 < 20 &&
            mapGV[row - i][col] == mapGV[row - i + 1][col] &&mapGV[row - i][col] == mapGV[row - i + 2][col] &&mapGV[row - i][col] == mapGV[row - i + 3][col] && mapGV[row - i + 4][col] !=-1)
            num1=1;
    }
    // 左斜方向
    for (int i = 0; i < 4; i++)
    {
        if (row + i < 20 &&row + i - 3 > 0 &&col - i > 0 &&col - i +3 < 20 &&
            mapGV[row + i][col - i] == mapGV[row + i - 1][col - i + 1] &&mapGV[row + i][col - i] == mapGV[row + i - 2][col - i + 2] &&mapGV[row + i][col - i] == mapGV[row + i - 3][col - i + 3]&&mapGV[row + i - 4][col - i + 4]!=-1)
            num2=1;
    }

    // 右斜方向
    for (int i = 0; i < 4; i++)
    {
        if (row - i > 0 &&row - i + 3 < 20 &&col - i > 0 &&col - i + 3 < 20 &&
            mapGV[row - i][col - i] == mapGV[row - i + 1][col - i + 1] &&mapGV[row - i][col - i] == mapGV[row - i + 2][col - i + 2] &&mapGV[row - i][col - i] == mapGV[row - i + 3][col - i + 3]&&mapGV[row - i + 4][col - i + 4]!=-1)
            num3=1;
    }

    if(num+num1+num2+num3==2){
        return true;
    }
    return false;
}

bool chess::isFive(int row, int col)
{
    int num=0,num1=0,num2=0,num3=0;
    for (int i = 0; i < 4; i++)
    {
        // 往左4个，往右匹配3个子，20种情况
        if (col - i > 0 &&col - i + 3 < 20 &&
                mapGV[row][col - i] == mapGV[row][col - i + 1] &&mapGV[row][col - i] == mapGV[row][col - i + 2] &&mapGV[row][col - i] == mapGV[row][col - i + 3]&&mapGV[row][col - i] == mapGV[row][col - i + 4] &&mapGV[row][col - i + 5]!=-1 )
            num=1;
    }

    // 竖直方向(上下延伸5个)
    for (int i = 0; i < 4; i++)
    {
        if (row - i > 0 &&row - i + 3 < 20 &&
                mapGV[row - i][col] == mapGV[row - i + 1][col] &&mapGV[row - i][col] == mapGV[row - i + 2][col] &&mapGV[row - i][col] == mapGV[row - i + 3][col]&&mapGV[row - i][col] == mapGV[row - i + 4][col]&&mapGV[row - i + 5][col]!=-1 )
            num1=1;
    }
    // 左斜方向
    for (int i = 0; i < 4; i++)
    {
        if (row + i < 20 &&row + i - 3 > 0 &&col - i > 0 &&col - i +3 < 20 &&
                mapGV[row + i][col - i] == mapGV[row + i - 1][col - i + 1] &&mapGV[row + i][col - i] == mapGV[row + i - 2][col - i + 2] &&mapGV[row + i][col - i] == mapGV[row + i - 3][col - i + 3]&&mapGV[row + i][col - i] == mapGV[row + i - 4][col - i + 4]&&mapGV[row + i - 5][col - i + 5]!=-1)
            num2=1;
    }

    // 右斜方向
    for (int i = 0; i < 4; i++)
    {
        if (row - i > 0 &&row - i + 3 < 20 &&col - i > 0 &&col - i + 3 < 20 &&
                mapGV[row - i][col - i] == mapGV[row - i + 1][col - i + 1] &&mapGV[row - i][col - i] == mapGV[row - i + 2][col - i + 2] &&mapGV[row - i][col - i] == mapGV[row - i + 3][col - i + 3]&&mapGV[row - i][col - i] == mapGV[row - i + 4][col - i + 4]&&mapGV[row - i + 5][col - i + 5]!=-1)
            num3=1;
    }
    if(num+num1+num2+num3==2){
        return true;
    }
    return false;
}

//禁手
void chess::actAI(int &row, int &col)
{
    // 计算评分
    cScore();

    // 从评分中找出最大分数的位置
    int maxscore = 0;
    std::vector<std::pair<int, int>> max;

    for (int row = 1; row < 20; row++)
        for (int col = 1; col < 20; col++)
        {
            if (mapGV[row][col] == 0)
            {
                if (mapSV[row][col] > maxscore)          // 找最大的数和坐标
                {
                    max.clear();
                    maxscore = mapSV[row][col];
                    max.push_back(std::make_pair(row, col));
                }
                else if (mapSV[row][col] == maxscore)     // 有多个最大的数
                    max.push_back(std::make_pair(row, col));
            }
        }

    // 随机落子
    srand((unsigned)time(0));
    int index = rand() % max.size();
    std::pair<int, int> pair = max.at(index);
    row =pair.first; // 记录落子点
    col = pair.second;
    updateMap(row,col);
}
void chess::actAIAfter(int &row, int &col)
{
    // 计算评分
    cScore1();
    // 从评分中找出最大分数的位置
    int maxscore = 0;
    std::vector<std::pair<int, int>> max;

    for (int row = 1; row < 20; row++)
        for (int col = 1; col < 20; col++)
        {
            if (mapGV[row][col] == 0)
            {
                if (mapSV[row][col] > maxscore)          // 找最大的数和坐标
                {
                    max.clear();
                    maxscore = mapSV[row][col];
                    max.push_back(std::make_pair(row, col));
                }
                else if (mapSV[row][col] == maxscore)     // 如果有多个最大的数，都存起来
                    max.push_back(std::make_pair(row, col));
            }
        }

    // 随机落子
    srand((unsigned)time(0));
    int index = rand() % max.size();
    std::pair<int, int> pair = max.at(index);
    row =pair.first; // 记录落子点
    col = pair.second;
    mapGV[row][col] = 1;
}

// 最关键的计算评分函数
void chess::cScore()
{
    // 清空评分数组
    mapSV.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> line;
        for (int j = 0; j < 20; j++)line.push_back(0);
        mapSV.push_back(line);
    }

    // 计分
    for (int row = 0; row < 20; row++)
        for (int col = 0; col < 20; col++)
        {
            // 空白点就算
            if (row > 0 && col > 0 &&
                mapGV[row][col] == 0)
            {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personN = 0;
                        AIN = 0;
                        empty = 0;

                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子

                            // 对玩家评分（正反两个方向）
                            for (int i = 1; i <= 5; i++)
                            {
                                if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row + i * y][col + i * x] == 1) // 玩家的子
                                {
                                    personN++;
                                }
                                else if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row + i * y][col + i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 5; i++)
                            {
                                if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == 1) // 玩家的子
                                {
                                    personN++;
                                }
                                else if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (personN == 1)                      // 杀二
                                mapSV[row][col] += 10;
                            else if (personN == 2)                 // 杀三
                            {
                                if (empty == 1)
                                    mapSV[row][col] += 30;
                                else if (empty == 2)
                                    mapSV[row][col] += 40;
                            }
                            else if (personN == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (empty == 1)
                                    mapSV[row][col] += 60;
                                else if (empty == 2)
                                    mapSV[row][col] += 110;

                            }
                            else if (personN == 4)  {               // 杀五
                                if (empty == 1)
                                    mapSV[row][col] += 80;
                                else if (empty == 2)
                                    mapSV[row][col] += 150;

                            }
                            else if (personN == 5)                 // 杀六
                                mapSV[row][col] += 10100;
                            // 进行一次清空
                            empty = 0;

                            // 对AI黑子评分
                            for (int i = 1; i <= 5; i++)
                            {
                                if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row + i * y][col + i * x] == 1) // 玩家的子
                                {
                                    AIN++;
                                }
                                else if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row +i * y][col + i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 5; i++)
                            {
                                if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == -1) // AI的子
                                {
                                    AIN++;
                                }
                                else if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (AIN == 0)                      // 普通下子
                                mapSV[row][col] += 5;
                            else if (AIN == 1)                 // 活二
                                mapSV[row][col] += 10;
                            else if (AIN == 2)
                            {
                                if (empty == 1)                // 死三
                                    mapSV[row][col] += 25;
                                else if (empty == 2)
                                    mapSV[row][col] += 50;  // 活三
                            }
                            else if (AIN == 3)
                            {
                                if (empty == 1)                // 死四
                                    mapSV[row][col] += 60;
                                else if (empty == 2){
                                    mapSV[row][col] += 100;
                                }// 活四
                            }
                            else if (AIN == 4)
                            {
                                if (empty == 1)                // 死五
                                    mapSV[row][col] += 500;
                                else if (empty == 2)
                                    mapSV[row][col] += 1110; // 活五
                            }
                            else if (AIN >= 5)
                                mapSV[row][col] += 10000;   // 活六

                        }
                    }

            }
        }
}
void chess::cScore1()
{
    // 清空评分数组
    mapSV.clear();
    for (int i = 0; i < 20; i++)
    {
        std::vector<int> line;
        for (int j = 0; j < 20; j++)line.push_back(0);
        mapSV.push_back(line);
    }

    // 计分
    for (int row = 0; row < 20; row++)
        for (int col = 0; col < 20; col++)
        {
            // 空白点就算
            if (row > 0 && col > 0 &&
                mapGV[row][col] == 0)
            {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personN = 0;
                        AIN = 0;
                        empty = 0;

                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子

                            // 对玩家评分（正反两个方向）
                            for (int i = 1; i <= 5; i++)
                            {
                                if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row + i * y][col + i * x] == -1) // 玩家的子
                                {
                                    personN++;
                                }
                                else if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row + i * y][col + i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 5; i++)
                            {
                                if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == -1) // 玩家的子
                                {
                                    personN++;
                                }
                                else if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (personN == 1)                      // 杀二
                                mapSV[row][col] += 10;
                            else if (personN == 2)                 // 杀三
                            {
                                if (empty == 1)
                                    mapSV[row][col] += 30;
                                else if (empty == 2)
                                    mapSV[row][col] += 40;
                            }
                            else if (personN == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (empty == 1)
                                    mapSV[row][col] += 60;
                                else if (empty == 2)
                                    mapSV[row][col] += 110;

                            }
                            else if (personN == 4)  {               // 杀五
                                if (empty == 1)
                                    mapSV[row][col] += 80;
                                else if (empty == 2)
                                    mapSV[row][col] += 150;

                            }
                            else if (personN == 5)                 // 杀六
                                mapSV[row][col] += 10100;
                            // 进行一次清空
                            empty = 0;

                            // 对AI黑子评分
                            for (int i = 1; i <= 5; i++)
                            {
                                if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row + i * y][col + i * x] == -1) // 玩家的子
                                {
                                    AIN++;
                                }
                                else if (row + i * y > 0 && row + i * y < 20 &&col + i * x > 0 && col + i * x < 20 &&mapGV[row +i * y][col + i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 5; i++)
                            {
                                if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == 1) // AI的子
                                {
                                    AIN++;
                                }
                                else if (row - i * y > 0 && row - i * y < 20 &&col - i * x > 0 && col - i * x < 20 &&mapGV[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    empty++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (AIN == 0)                      // 普通下子
                                mapSV[row][col] += 5;
                            else if (AIN == 1)                 // 活二
                                mapSV[row][col] += 10;
                            else if (AIN == 2)
                            {
                                if (empty == 1)                // 死三
                                    mapSV[row][col] += 25;
                                else if (empty == 2)
                                    mapSV[row][col] += 50;  // 活三
                            }
                            else if (AIN == 3)
                            {
                                if (empty == 1)                // 死四
                                    mapSV[row][col] += 60;
                                else if (empty == 2){
                                    mapSV[row][col] += 100;
                                }// 活四
                            }
                            else if (AIN == 4)
                            {
                                if (empty == 1)                // 死五
                                    mapSV[row][col] += 500;
                                else if (empty == 2)
                                    mapSV[row][col] += 1110; // 活五
                            }
                            else if (AIN >= 5)
                                mapSV[row][col] += 10000;   // 活六

                        }
                    }

            }
        }
}
