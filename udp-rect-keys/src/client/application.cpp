#include "application.h"

#include <SFML/Window/Event.hpp>
#include <iostream>

#include "../common/net_helper.h"

Application::Application()
    : m_client(sf::IpAddress::LocalHost, PORT)
    //, m_player(m_players[m_client.clientId()])
{
    /*
    m_player.sprite.setPosition({20, 20});
    m_player.sprite.setFillColor(sf::Color::Red);

    if (m_client.isConnected()) {
        m_player.isConnected = true;
        auto packet =
            makePacket(Command::GetPlayerPositions, m_client.clientId());
        m_client.send(packet);
    }*/
}

void Application::run()
{
    //if (!m_client.isConnected()) {
    //    return;
    //}
    m_window.create({WINDOW_WIDTH, WINDOW_HEIGHT}, "UDP Socket playground");
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);

    constexpr unsigned TPS = 30; // ticks per seconds
    const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));

    sf::Clock timer;
    sf::Clock netTimer;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    while (m_window.isOpen()) {
        // Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        input();
        while (lag >= timePerUpdate) {
            lag -= timePerUpdate;
            update(timer, elapsed);
        }
        /*
        if (netTimer.getElapsedTime().asMilliseconds() > 20) {
            auto packet = makePacket(Command::KeepAlive, m_client.clientId());
            m_client.send(packet);

            packet = makePacket(Command::PlayerPosition, m_client.clientId());
            packet << m_player.sprite.getPosition().x
                   << m_player.sprite.getPosition().y;
            m_client.send(packet);

            netTimer.restart();

            packet =
                makePacket(Command::GetPlayerPositions, m_client.clientId());
            m_client.send(packet);
        }
        */

        render();
    }
}

void Application::input()
{
    pollWindowEvents();
/*
    // Input
    if (m_keyboard.isKeyDown(sf::Keyboard::Up)) {
        m_player.velocity.y += -0.1;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::Down)) {
        m_player.velocity.y += 0.1;
    }
    if (m_keyboard.isKeyDown(sf::Keyboard::Left)) {
        m_player.velocity.x += -0.1;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::Right)) {
        m_player.velocity.x += 0.1;
    }*/
}

void Application::update(sf::Clock &elapsed, sf::Time delta)
{
    (void)delta;
    (void)elapsed;
/*
    m_player.sprite.move(m_player.velocity);
    m_player.velocity.x *= 0.98;
    m_player.velocity.y *= 0.98;

    const float x = m_player.sprite.getPosition().x;
    const float y = m_player.sprite.getPosition().y;

    if (x + PLAYER_WIDTH > WINDOW_WIDTH) {
        m_player.sprite.setPosition(WINDOW_WIDTH - PLAYER_WIDTH - 1, y);
    }
    if (y + PLAYER_HEIGHT > WINDOW_HEIGHT) {
        m_player.sprite.setPosition(x, WINDOW_HEIGHT - PLAYER_HEIGHT - 1);
    }
    if (x < 0) {
        m_player.sprite.setPosition(1, y);
    }
    if (y < 0) {
        m_player.sprite.setPosition(x, 1);
    }

    for (auto &player : m_players) {
        if (&player == &m_player)
            continue;
        player.sprite.setPosition(player.nextPosition.x, player.nextPosition.y);
        auto lerp = [](float a, float b, float t) {
            return (1 - t) * a + t * b;
        };
        player.lerpValue += 0.5 * delta.asSeconds();
        auto newX = lerp(player.sprite.getPosition().x, player.nextPosition.x,
                         player.lerpValue);
        auto newY = lerp(player.sprite.getPosition().y, player.nextPosition.y,
                         player.lerpValue);

        player.sprite.setPosition(newX, newY);
    }

    handleIncomingPacket();*/
}

void Application::render()
{
    
    m_window.clear();
/*
    for (auto &player : m_players) {
        if (player.isConnected) {
            m_window.draw(player.sprite);
        }
    }
*/
    m_window.display();
}
/*
void Application::handleIncomingPacket()
{
    RecievedCommandInfo info;
    sf::Packet packet;
    while (m_client.recievePacket(info, packet)) {

        if (info.id == m_client.clientId()) {
            continue;
        }
        auto &player = m_players[info.id];
        player.isConnected = true;

        switch (info.command) {
            case Command::PlayerPosition:
                handleRecPlayerPosition(player, packet);
                break;

            default:
                break;
        }
    }
}
*/
void Application::pollWindowEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        m_keyboard.update(e);
        switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;

            default:
                break;
        }
    }
}
/*
void Application::handleRecPlayerPosition(Player &player, sf::Packet &packet)
{
    packet >> player.nextPosition.x >> player.nextPosition.y;
    player.lerpValue = 0;
}
*/
// http://enet.bespin.org/Tutorial.html