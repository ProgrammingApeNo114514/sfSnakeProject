# workdiary

## 20240508 - 20240521

##### 配置环境：

###### 1.采用vscode(failed):

    尝试Cmake中利用`fetchcontent` 从github下载SFML库，但运行后显示`#include<SFML/Graphic.hpp>   no such file or directory`
尝试先将SFML库下载到目标文件夹内，再用Cmake进行库的链接，能够成功编译生成exe文件，但是运行时显示缺乏各类`.dll`文件，将这些文件补充上后，显示`无法定位程序输入点......于动态链接库MSVCP140D.dll上`,上网搜得不到答案，遂放弃.

###### 2.采用visual studio + vcpkg:

    下载`visual studio 2022 preview` 作为IDE
    在命令行中输入 `git clone https://github.com/Microsoft/vcpkg` 进行vcpkg包管理器下载
    输入`.\bootstrap-vcpkg.bat` vcpkg下载完成
    输入`.\vcpkg install sfml:x64-windows` 下载sfml库
    在visual studio中与`vcpkg.exe`链接， 再设置系统变量
    编写cmake文件, 并进行生成，至此环境配置完成

---

## 20240522 - 20240525

### have the main part done : the change of the structure of `class Snake`

#### modification in the concept of```class SnakeNode``` :

     I changed the kind of STL containers for a object in `class Snake` to reserve a sequence of `class SnakeNode`, the original container was `std::vector<SnakeNode>` , which have a time complexity of o(n) when you want to add an element at the front. In my program, I adjust it to `std::deque<Snake>` , which in contrast have a time complexity of o(1).

    Then, For example, if we defined `Snake snake` , and we have a member of `snake` : `std::deque<SnakeNode> nodes_` , in the original progr-am, each `nodes_` represents a bodypart of snake, this definitely contains less space for only four directions for the snake. But I want to steel the snake with my mouse, which means I have to change the  `direction_` from an `enum class` of four directions to a vector from the head of the snake pointing to the position of the mouse. We assume that the snake have a length of  $r$ .Apparently, if I want the snake to move smoothly, it isn't enough to have $r$ nodes to describe the movement of the snake. 

    So I introduced another kind of expression, a snake with a length of $r$ would have  $nodes\_.size( ) = 10\cdot(r - 1)+ 1$, set the headnode as `nodes_[0]` , and the endnode as `node[nodes_size()]` , and set the distance between two nodes is 10 times smaller than the former, which ensures that the length in total doesn't change. Then we can let $nodes\_[0 + 10 \cdot i]$ be the bodypart of the snake. Thus every time we update the position of the snake, we can simply delete that last few nodes and add them at the head of the snake, and from that we can see the advantage of use `std::deque` as the container.

#### change the functions in `snake.cpp`

###### 1. modify `void Snake::initNodes()`

```cpp
void Snake::initNodes()
{
    for (int i = 0; i <= 10 * (Snake::InitialSize - 1); ++i)
    {
        sf::Vector2f Initial_Position;
        Initial_Position.x = Game::Width / 2 - SnakeNode::BodyDiameter / 2;
        Initial_Position.y = Game::Height / 2 - SnakeNode::BodyDiameter / 2 + SnakeNode::NodeLen * i;

        nodes_.push_back(Initial_Position);
    }
}
```

###### 2. modify `void Snake::handleInput(sf::RenderWindow& window)`

description : add a way to steel the snake with the mouse

```cpp
void Snake::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction_ = sf::Vector2f(0, -1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction_ = sf::Vector2f(0, 1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction_ = sf::Vector2f(-1.f, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction_ = sf::Vector2f(1.f, 0);

    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f HeadPosition = nodes_[0].getPosition(); 
        direction_.x = MousePosition.x - HeadPosition.x;
        direction_.y = MousePosition.y - HeadPosition.y; 
        direction_ = Unitize(direction_);
    }
}
```

###### 3.modify `void Snake::move() `

description : delete the last 1 or 2 nodes (2 means in accelerate mode), then add the same amount of nodes at the front based on then moving direction of the snake

```cpp
void Snake::move() 
{
 int MoveNodes;
 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
 MoveNodes = 2;
 else MoveNodes = 1; 
for (int i = 1; i <= MoveNodes; ++i) 
{
 nodes_.pop_back();
 nodes_.push_front(
 nodes_[0].getPosition() + direction_ * SnakeNode::NodeLen  
 );
 }
}
```

###### 4. modify `void Snake::grow()`

description : get the direction of the last two nodes in order to get the direction_ of the snake , then add 10 nodes 

```cpp
void Snake::grow()
{
    sf::Vector2f EndPosition = nodes_[nodes_.size() - 1].getPosition();
    sf::Vector2f EndDirection = sf::Vector2f(EndPosition - nodes_[nodes_.size() - 2].getPosition());

    EndDirection = Unitize(EndDirection);

    for (int i = 1; i <= 10; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(EndPosition.x + i * EndDirection.x, 
                                                                            EndPosition.y + i * EndDirection.y)));
    }
}
```

###### 5. add `sf::Vector2f Unitize(sf::Vector2f number)`

description : once get a `direction_` , we need to unitize it. 

```cpp
sf::Vector2f Unitize(sf::Vector2f number)
{
    number.x = number.x / sqrt(number.x * number.x + number.y * number.y);
    number.y = sqrt(1 - number.x * number.x) * number.y / abs(number.y);
    return number;
}
```

These are the main functions that I modified based on the original version of the program. the video following is a peoriodical accomplish-ment.

## 20240525

#### structure optimization:

    Put all the source code in a folder named `sources`, which contains four subfolders named `fruit` , `game`, `snake` and `screens`, all the source texts are classified based on these four folders.

    then do such addings in CmakeLists.txt

```cmake
include_directories(./sources/fruit)
include_directories(./sources/game)
include_directories(./sources/screens)
include_directories(./sources/snake)
```

```cmake
file(GLOB_RECURSE SOURCES "sources/*.cpp")

add_executable(sfsnake ${SOURCES})
```

## 20240528

#### modification in the generation of fruit:

    In the original program, there is only one fruit on the screen, and when the snake eat the fruit, another fruit will be immediately generat-ed, and can only generate fruit with red color.

###### generate a fruit every several seconds:

    In my program, I set a const float named `generatefruitfrequency = 2.f` which means generate a fruit every 2 seconds. To achieve this goal, I create a flag which was initialized as `sf::Time generatefruitflag = sf::Time::Zero`, and send as a parameter to the function  `update(sf::Time delta, sf::Time& generatefruiflag)` , and this flag times since the screen turns to `GameScreen` and when it counts to `generatefruitfrequency` then invocate the function `generatefruit()` , and let `generatefruitflag = sf::Time::Zero` again. Thus we can generate a fruit every 2s.

###### randomly generate different colors of fruit:

    Firstly, I add a `enum class Color` that contains `Black, Brown, Red, Green, Blue` , then add a private number in `class Fruit` which is `Color fruitcolor` , and add 2 extra parameter in the default constructor of `class Fruit` , the function then turns to `Fruit(sf::Vector2f position = sf::Vector2f(0, 0), sf::Color color = sf::Color::Black, Color enumcolor = Color::Black)`

    Second, I changed the structure of `GameScreen::generatefruit()` in `GameScreen.cpp` , I defined `const float UselessFruitRatio = 0.25;`  , which means that the ratio of the fruit with `Color::Black` or `Color::Brown` will be around 25% (because later I would make diffe-rent color of fruit increases different length of the snake, and the color of Black or Brown doesn't increases the length, so I call them useless fruit), and the ratio of the others will be 75%. I created an unordered_map in `class GameScreen`: `std::unordered_map<Color, int> fruitnum = { {Color::Black, 0}, {Color::Brown, 0}, {Color::Red, 0}, {Color::Green, 0}, {Color::Blue, 0} };` , which can save the number of each type of fruit at present. 

```cpp
void GameScreen::generateFruit()
{
    static std::default_random_engine engine;
    engine.seed(time(NULL));
    static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::BodyDiameter);
    static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::BodyDiameter);

    std::uniform_int_distribution<int> colornum;
    std::cout << fruitnum.at(Color::Black) + fruitnum.at(Color::Brown) << ' ' << fruit_.size() << '\n';
     if ((fruitnum.at(Color::Black) + fruitnum.at(Color::Brown)) / UselessFruitRatio < fruit_.size() ) {
        colornum = std::uniform_int_distribution<int>(0, 1);
    }
    else {
        colornum = std::uniform_int_distribution<int>(2, 4);
    }

    switch (colornum(engine))
    {
        case int(Color::Black):
            fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Black, Color::Black));
            AddFruit(Color::Black);
            break;

        case int(Color::Brown) :
            fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color(139,69,19), Color::Brown));
            AddFruit(Color::Brown);
            break;

        case int(Color::Red):
            fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Red, Color::Red));
            AddFruit(Color::Red);
            break;

        case int(Color::Green):
            fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Green, Color::Green));
            AddFruit(Color::Green);
            break;

        case int(Color::Blue):
            fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), sf::Color::Blue, Color::Blue));
            AddFruit(Color::Blue);
            break;
    }
```

## 20240529

##### Add grid in the GameScreen:

    In my program, I declared `class Grid` in `Grid.h` :

```cpp
#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid
{
public:
    Grid(int gridSize, int width, int height);

    void setGridColor(sf::Color color);

    void draw(sf::RenderWindow& window);

private:
    int m_gridSize;
    int m_width;
    int m_height;
    sf::Color m_gridColor;
};

#endif 
```

     Then I defined the functions that I declared in `Grid.h` in `Grid.cpp` :

```cpp
#include "Grid.h"

Grid::Grid(int gridSize, int width, int height)
    : m_gridSize(gridSize), m_width(width), m_height(height)
{
    m_gridColor = sf::Color(128, 128, 128); // 网格线颜色，默认为灰色
}

void Grid::setGridColor(sf::Color color)
{
    m_gridColor = color;
}

void Grid::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < m_width; x += m_gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, 0), m_gridColor),
            sf::Vertex(sf::Vector2f(x, m_height), m_gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    for (int y = 0; y < m_height; y += m_gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, y), m_gridColor),
            sf::Vertex(sf::Vector2f(m_width, y), m_gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
}
```

    Then I declared `Grid grid_` in `Class GameScreen` and initialized it in the constructor function of `GameScreen` 

```cpp
GameScreen::GameScreen() : snake_(), isgridon(true), grid_(50, 1280, 960)
{
    bgcolor = sf::Color::White;
}
```

## 20240530 - 20240601

##### Add `class Button` and `class TextButton` :

```cpp
//class Button
namespace sfSnake {
    class Button
    {
    public:
        Button();
        Button(const sf::Vector2f& position, const sf::Vector2f& scale, const std::string& filename);

        bool MouseOnButton(sf::RenderWindow& window);
        bool ButtonPressed(sf::RenderWindow& window);

        void render(sf::RenderWindow& window) const;
    private:
        sf::Sprite sprite_;
        sf::Texture texture_;
    };
}
```

```cpp
//class TextButton
namespace sfSnake {
    class TextButton
    {
    public:
        TextButton();
        TextButton(const sf::Vector2f& position, const std::string& text);

        bool MouseOnButton(sf::RenderWindow& window);
        bool ButtonPressed(sf::RenderWindow& window);

        void render(sf::RenderWindow& window);

        void ChangeColor(sf::Color color);
        sf::Color GetColor();

        void operator=(const TextButton& button);
    private:
        sf::Text text_;
        sf::Font font_;
    };
}
```

then I defined the members of `class Button` and `class TextButton` in `Button.cpp` and `TextButton.cpp` 

##### Add PauseScreen:

I added a pausescreen that can be visited through the pausebutton in the gamescreen  

<img src="file:///C:/Users/86156/Pictures/Screenshots/屏幕截图%202024-06-04%20222155.png" title="" alt="" width="295">

then I created `PauseScreen.h` and `PauseScreen.cpp` to define `class PauseScreen`, which has four buttons:

1. `gobackbutton` to go back to the game

2. `optionbutton` to go to the `OptionScreen` 

3. `restartbutton` to restart

4. `quitbutton` to go back to main menu

5. show the current score in the middle of the screen

6. `Help` button to the helpscreen

<img src="file:///C:/Users/86156/Pictures/Screenshots/屏幕截图%202024-06-04%20223738.png" title="" alt="" width="296">

```cpp
//class PauseScreen
namespace sfSnake
{
    class PauseScreen : public Screen
    {
    public:
        PauseScreen(std::shared_ptr<GameScreen>& gamescreen, const int& score);

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta, sf::Time& generatefruitflag) override;
        void render(sf::RenderWindow& window) override;

        std::shared_ptr<GameScreen> GetGameScreen();

    private:
        sf::Font font_;

        sf::Text pausetext_;
        sf::Text scoretext_;

        sf::Color bgcolor;
        std::shared_ptr<GameScreen> gamescreen_;

        Button continuebutton1;
        Button continuebutton2;

        Button optionbutton1;
        Button optionbutton2;

        Button restartbutton1;
        Button restartbutton2;

        Button quitbutton1;
        Button quitbutton2;

        TextButton helpbutton;
    };
}
```

to reserve the current game, I set the current gamescreen as a parameter into the contruct function of `Pausescreen` and let `PauseScreen::gamescreen_` to reserve the current gamescreen.

## 20240602 - 20240604

##### Add OptionScreen:

there are 3 options which are showed in the following picture:

<img src="file:///C:/Users/86156/Pictures/Screenshots/屏幕截图%202024-06-04%20224600.png" title="" alt="" width="319">

to achieve this, I set the construct function of `class OptionScreen` by this : 

```cpp
OptionScreen(std::shared_ptr<PauseScreen>& pausescreen);
OptionScreen(std::shared_ptr<MenuScreen>& menuscreen, std::shared_ptr<GameScreen>& gamescreen);
```

and `OptionScreen.h` :

```cpp
//class OptionScreen
namespace sfSnake
{
    class OptionScreen : public Screen
    {
    public : 
        OptionScreen(std::shared_ptr<PauseScreen>& pausescreen);
        OptionScreen(std::shared_ptr<MenuScreen>& menuscreen, std::shared_ptr<GameScreen>& gamescreen);

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta, sf::Time& generatefruitflag) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font font_;

        sf::Text optiontext_;
        sf::Color bgcolor;
        std::shared_ptr<PauseScreen> pausescreen_;
        std::shared_ptr<MenuScreen> menuscreen_;

        Button gobackbutton1;
        Button gobackbutton2;

        sf::Text optionlist_;

        TextButton grid_on; 
        TextButton grid_off;

        TextButton grid_black;
        TextButton grid_white;
        TextButton grid_brown;

        TextButton bg_black;
        TextButton bg_white;
        TextButton bg_brown;
    };
}
```

1. when we get to the optionscreen from pausescreen , call the first construct function, and send the current pausescreen as a parameter, then we can use `PauseScreen::gamescreen_` to visit the gamescreen, thus we can visit and change the members of the current gamescreen .

2. samely, when we get to the optionscreen from menuscreen, call the second construct function, and set the gamescreen from the very start. 

##### Modify menuscreen :

there are several buttons added in the menuscreen as the following picture shows : 

<img src="file:///C:/Users/86156/Pictures/Screenshots/屏幕截图%202024-06-05%20132442.png" title="" alt="" width="316">

## 20240606 - 20240608

##### Optimize the apperance of the snake:

use `sf::Sprite` to draw the head of the snake, and add some black Rectangles as the striation of the body of the snake.

<img src="file:///C:/Users/86156/Pictures/Screenshots/屏幕截图%202024-06-08%20142318.png" title="" alt="" width="316"> 

##### Optimize GameoverScreen:

three buttons are provided, one to go back to mainmenu, one to restart the game, one to quit the game.

<img src="file:///C:/Users/86156/Pictures/Screenshots/屏幕截图%202024-06-08%20142812.png" title="" alt="" width="317">
