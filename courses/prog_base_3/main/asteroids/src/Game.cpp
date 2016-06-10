#include "Game.h"

Game::Game(): window("Asteroids!", sf::Vector2u(W,H))
{
    window.GetRenderWindow()->setFramerateLimit(60);

    tSpaceship.loadFromFile("images/spaceship.png");
    tBackground.loadFromFile("images/background.jpg");
    tRockExplosion.loadFromFile("images/explosions/type_C.png");
    tRock.loadFromFile("images/rock.png");
    tFireBlue.loadFromFile("images/fire_blue.png");
    tRockSmall.loadFromFile("images/rock_small.png");
    tShipExplosion.loadFromFile("images/explosions/type_B.png");
    tBulletPowerup.loadFromFile("images/fire_red.png");

    tSpaceship.setSmooth(true);
    tBackground.setSmooth(true);

    background.setTexture(tBackground);

    aExplosion.Settings(tRockExplosion, 0,0,256,256, 48, 0.5);
    aRock.Settings(tRock, 0,0,64,64, 16, 0.2);
    aRock_small.Settings(tRockSmall, 0,0,64,64, 16, 0.2);
    aBullet.Settings(tFireBlue, 0,0,32,64, 16, 0.8);
    aPlayer.Settings(tSpaceship, 40,0,40,40, 1, 0);
    aPlayer_go.Settings(tSpaceship, 40,40,40,40, 1, 0);
    aExplosion_ship.Settings(tShipExplosion, 0,0,192,192, 64, 0.5);
    aBulletPowerup.Settings(tBulletPowerup, 0,0,32,64, 16, 0.8);

    for(int i=0;i<10;i++)
    {
      asteroid *aster = new asteroid();
      aster->settings(aRock, rand()%W, rand()%H, rand()%260, 25);
      entities.push_back(aster);
    }

    p->settings(aPlayer,W/2,H/2,0,20);
    entities.push_back(p);
    /*
    font.loadFromFile("font.ttf");

    text.setString("");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setColor(Color::Blue);
	text.setStyle(Text::Bold);
	text.setPosition(40, 40);

    time.setString("");
    time.setFont(font);
    time.setCharacterSize(20);
    time.setColor(Color::White);
    time.setStyle(Text::Bold);
    time.setPosition(130, 40);

    notif.setString("");
    notif.setFont(font);
    notif.setCharacterSize(20);
    notif.setStyle(Text::Bold);
    notif.setPosition(W/2 - 50, H/2 - 50);
    */
    gameTime = 0;

    gameClock.restart();

    music.openFromFile("music.ogg");
    music.play();
    music.setLoop(true);

    buffer.loadFromFile("powerup.wav");
    powerupS.setBuffer(buffer);

    buffer1.loadFromFile("explode.wav");
    explodeS.setBuffer(buffer1);

    buffer2.loadFromFile("meteor.wav");
    meteorS.setBuffer(buffer2);

}

gameWindow* Game::GetWindow()
{
    return &window;
}

bool isColide(Entity *a,Entity *b)      //CHECK COLLISION BETWEEN TWO CIRCLES
    {
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}

void Game::HandleInput()
{
    Event event;
        while (window.GetRenderWindow()->pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
             if (event.key.code == Keyboard::Space)
              {
                  if(p->getPowerUpStatus()== 0){
                        bullet *b0 = new bullet();
                        b0->settings(aBullet,p->x,p->y,p->angle,10);
                        entities.push_back(b0);
                  }
                  else if(p->getPowerUpStatus()== 1){
                        bullet *b1 = new bullet();
                        b1->settings(aBullet,p->x,p->y,p->angle - 10,10);
                        entities.push_back(b1);
                        bullet *b2 = new bullet();
                        b2->settings(aBullet,p->x,p->y,p->angle + 10,10);
                        entities.push_back(b2);
                  }
                   else if(p->getPowerUpStatus()== 2){
                        bullet *b3 = new bullet();
                        b3->settings(aBullet,p->x,p->y,p->angle - 15,10);
                        entities.push_back(b3);
                        bullet *b4 = new bullet();
                        b4->settings(aBullet,p->x,p->y,p->angle + 15,10);
                        entities.push_back(b4);
                        bullet *b5 = new bullet();
                        b5->settings(aBullet,p->x,p->y,p->angle ,10);
                        entities.push_back(b5);
                   } else{
                        bullet *b6 = new bullet();
                        b6->settings(aBullet,p->x,p->y,p->angle,10);
                        entities.push_back(b6);
                   }
              }
        }
    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=p->turnSpeed;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=p->turnSpeed; // CREATE FIELD TURN SPEED
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true; //TO DO: ADD POWERUPS THAT GIVE U BIGGER INERTION AND turn SPEED
    else p->thrust=false;
}

void Game::Update(){
    window.Update();


    for(auto a:entities)  // CHECKING THE COLLISION BETWEEN ASTEROIDS AND BULLETS, PLAYER AND ASTEROIDS, PLAYER AND POWERUPS
     for(auto b:entities)
    {
      if (a->name=="asteroid" && b->name=="bullet")
       if ( isColide(a,b) )
           {
            a->life=false;
            b->life=false;

            Entity *e = new Entity();
            e->settings(aExplosion,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            meteorS.play();

            if(rand()%100 > 95){
            powerup *pow = new powerup();
            pow->settings(aBulletPowerup,a->x,a->y, rand()%360, 15);
            pow->name = "powerupBull";
            entities.push_back(pow);
            }else{
                if(rand()%100 > 95){
                powerup *pow = new powerup();
                pow->settings(aBulletPowerup,a->x,a->y, rand()%360, 15);
                pow->anim.sprite.setColor(Color::Cyan);
                pow->name = "powerupStats";
                entities.push_back(pow);
                }
            }

            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             Entity *e = new asteroid();
             e->settings(aRock_small,a->x,a->y,rand()%360,15);
             entities.push_back(e);
            }

           }

      if (a->name=="player" && b->name=="asteroid")
       if ( isColide(a,b) )
           {
            gameClock.restart();
            explodeS.play();
            b->life=false;
            //p->life=false;
            Entity *e = new Entity();
            e->settings(aExplosion_ship,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            p->hasLost = true;
           }

       if (a->name=="player" && b->name=="powerupBull")
       if ( isColide(a,b) )
           {
            b->life=false;
            p->addBullets();
            powerupS.play();
            //p->life=false;
           }
       if (a->name=="player" && b->name=="powerupStats")
       if ( isColide(a,b) )
           {
            b->life=false;
            p->addStats();
            powerupS.play(); //reinterpret_cast<player*>(a)
            //p->life=false;
           }
    }

    if(p->HasLost()){
            p->reset();
    }

    if (p->thrust)  p->anim = aPlayer_go;                    //FIRE WHILE THURSTING
    else   p->anim = aPlayer;

    for(auto e:entities)
     if (e->name=="explosion")                               //EXPLOSIONS TO END
      if (e->anim.isEnd()) e->life=0;

     if (rand()%100 < p->asteroidFrequency){                     // RANDOMLY CREATE ASTEROIDS
       asteroid *a = new asteroid();
       a->settings(aRock, 0,rand()%H, rand()%360, 25);
       entities.push_back(a);
     }

     for(auto i=entities.begin();i!=entities.end();)          //UPDATE ALL ENTITIES IN THE GAME
    {
      Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entities.erase(i); delete e;}
      else i++;
    }
    /*
    gameTime = (int)gameClock.getElapsedTime().asSeconds();
    gameTimeString.str(" ");
    gameTimeString << gameTime;
    // cout<<gameTimeString.str());
    text.setString("Time:");
    time.setString(gameTimeString.str());
    if(gameTime>5){
        notif.setString(gameTimeString.str());
    }else{
        notif.setString("");
    }
    */
}

void Game::Render(){
    window.BeginDraw();
    // Render here.
    window.GetRenderWindow()->draw(background);

    //window.GetRenderWindow()->draw(notif);
   for(auto i:entities)
     i->draw(window.GetRenderWindow());
    /*
    window.GetRenderWindow()->draw(text);
    window.GetRenderWindow()->draw(time);
    */
    window.EndDraw();
}



Game::~Game()
{
    //dtor
}
