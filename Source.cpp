#include <iostream>
#include "header.h"
#include "structures.h"

int main()
	{
		srand(time(nullptr));
		
		// Объект, который, собственно, является главным окном приложения
		RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		Game game;
		game.window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		game.window.setFramerateLimit(FPS);
		//создание объектов игры
		//ракетки
		RectangleShape leftBat, rightBat;
		initBat(game.leftBat, leftBatColor, leftBatStartPos);
		initBat(game.rightBat, rightBatColor, rightBatStartPos);


		//шарик
		CircleShape ball;
		initBall(ball, ballColor, ballStartPosition);
		float arr_speed[]{ -5.f,-4.f,-3.f,-2.f,-1.f,1.f,2.f,3.f,4.f,5.f };
		int index = rand() % 10;
		float ball_speedx = arr_speed[index];
		index = rand() % 10;
		float ball_speedy = arr_speed[index];
		initBall(game.ball);

		//счет
		int leftPlayerScore = 0;
		int rightPlayerScore = 0;


		Font font;
		font.loadFromFile("ds-digib.ttf");
		//1 Обрабатываем очередь событий в цикле
		Text leftPlayerScoreText;
		initText(leftPlayerScoreText, leftPlayerScore, font, charSize, leftTextStartPos);

		Text rightPlayerScoreText;
		initText(rightPlayerScoreText, rightPlayerScore, font, charSize, rightTextStartPos);
		game.font.loadFromFile("ds-digib.ttf");
		initText(game.leftPlayerScoreText, leftPlayerScore, game.font, charSize, leftTextStartPos);
		initText(game.rightPlayerScoreText, rightPlayerScore, game.font, charSize, rightTextStartPos);

		// Главный цикл приложения. Выполняется, пока открыто окно
		while (game.window.isOpen())
			@@ - 59, 28 + 35, 53 @@ int main()
			//2 Обновление объектов
		//шарик
		//движение шарика
			ball.move(ball_speedx, ball_speedy);
		game.ball.shape.move(game.ball.speedX, game.ball.speedY);
		Vector2f midLeft{ game.ball.shape.getPosition().x, game.ball.shape.getPosition().y + BALL_RADIUS };
		Vector2f midTop{ game.ball.shape.getPosition().x + BALL_RADIUS, game.ball.shape.getPosition().y };
		Vector2f midRight{ game.ball.shape.getPosition().x + 2 * BALL_RADIUS, game.ball.shape.getPosition().y + BALL_RADIUS };
		Vector2f midBottom{ game.ball.shape.getPosition().x + BALL_RADIUS, game.ball.shape.getPosition().y + 2 * BALL_RADIUS };
		//правый игрок забил гол
		if (ball.getPosition().x <= 0)
			ballReboundX(ball_speedx, rightPlayerScore,
				rightPlayerScoreText);
		if (game.ball.shape.getPosition().x <= 0) {
			ballReboundX(game.ball.speedX, rightPlayerScore,
				game.rightPlayerScoreText);
			initBall(game.ball);
			/*game.window.display();
			do {} while (!(Keyboard::isKeyPressed(Keyboard::Space)));*/
		}

		//èëè ïðàâóþ ãðàíèöó
		if (ball.getPosition().x >= (WINDOW_WIDTH - 2 * ballRadius))
			ballReboundX(ball_speedx, leftPlayerScore,
				leftPlayerScoreText);
		if (game.ball.shape.getPosition().x >=
			(WINDOW_WIDTH - 2 * BALL_RADIUS))
		{
			ballReboundX(game.ball.speedX, leftPlayerScore,
				game.leftPlayerScoreText);
			initBall(game.ball);
			/*game.window.display();
			do {} while (!(Keyboard::isKeyPressed(Keyboard::Space)));*/
		}
		//âåðõíÿÿ èëè íèæíÿÿ ãðàíèöû
		if (ball.getPosition().y <= 0 || ball.getPosition().y >=
			(WINDOW_HEIGHT - 2 * ballRadius))
			ball_speedy = -ball_speedy;

		controlBat(leftBat, leftBatSpeedY, Keyboard::W, Keyboard::S);
		controlBat(rightBat, rightBatSpeedY, Keyboard::Up, Keyboard::Down);
		if (game.ball.shape.getPosition().y <= 0 ||
			game.ball.shape.getPosition().y >=
			(WINDOW_HEIGHT - 2 * BALL_RADIUS)
			)
			game.ball.speedY = -game.ball.speedY;
		//îòáèâàíèå ìÿ÷à îò ðàêåòîê
		// ëåâîé ðàêåòêè
		if (pointInRect(game.leftBat, midLeft))
			game.ball.speedX = -game.ball.speedX;
		if (pointInRect(game.leftBat, midTop) || pointInRect(game.leftBat, midBottom))
			game.ball.speedY = -game.ball.speedY;
		//ïðàâàÿ
		if (pointInRect(game.rightBat, midRight))
			game.ball.speedX = -game.ball.speedX;
		if (pointInRect(game.rightBat, midTop) || pointInRect(game.rightBat, midBottom))
			game.ball.speedY = -game.ball.speedY;


		//3 Îòðèñîâêà îêíà
		drawAll(game.window, leftBat, rightBat, ball, leftPlayerScoreText, rightPlayerScoreText);
		controlBat(game.leftBat, Keyboard::W, Keyboard::S);
		controlBat(game.rightBat, Keyboard::Up, Keyboard::Down);


		drawAll(game);
	}
	return 0;
}