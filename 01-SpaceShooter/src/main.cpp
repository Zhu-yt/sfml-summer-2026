#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Shooter - Week 1");
    window.setFramerateLimit(60);

    //创建矩形，暂时当作飞机
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f,500.f);//飞机起始放在底部中间

    const float speed = 300.f;

    sf::Clock clock;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        // Delta Time: 让移动速度不受帧率影响
        float dt = clock.restart().asSeconds();

        //读取输入
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player.move(-speed * dt, 0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player.move(speed * dt, 0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.move(0.f, -speed * dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.move(0.f, speed * dt);
        }

        //边界限制
        if(player.getPosition().x < 0.f){
            player.setPosition(0.f, player.getPosition().y);
        }
        if(player.getPosition().x > 750.f){
            player.setPosition(750.f, player.getPosition().y);
        }
        if(player.getPosition().y < 0.f){
            player.setPosition(player.getPosition().x, 0.f);
        }
        if(player.getPosition().y > 550.f){
            player.setPosition(player.getPosition().x, 550.f);
        }

        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }

    return 0;
}