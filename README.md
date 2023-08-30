# Beef-like

## Unix system

У вас должен быть установлен python2.
Необходимо установить gcc и cmake.

### Run:

В root разделе напишите в терминале:

```bash
make
```

После компиляции нажмите ALT+ENTER.

### Список основных фичей:

1. В игре есть возможность ходить за еду. Для того, что бы выкинуть еду из инвентаря нажмите 'E'. Повторно нажмите 'E'
   что бы вернуться в тело игрока, соответственно меняется HUD.
   Будучи едой, вы можете собирать монетки, отвлекать врагов и активировать ловушки - капканы. У еды есть количество
   ходов, за которое за нее можно ходить, и хп,
   если количество ходов закончится, или у еды закончатся хп, то еда исчезнет.
2. В игре отображается фпс.
3. В игре есть инвентарь под хилки, еду и капканы. Нажмите 'Q' для свапа еды в инвентаре.
4. В random-map режиме у игрока есть область видимости, дальше которой он не видит.
5. В игре(random-map) есть два вида ловушек. Первый из них - шипы из пола. В случайный момент времени(действия персонажа) шипы могут
   перейти
   в состояние готовности(меняется текстура). На следующем ходу шипы приводятся в действие на случайное количество
   шагов. Второй вид ловушек - капканы.
   В открытом состоянии капкан может в случайный момент времени начать закрываться, во время закрытия меняется текстура.
   В закрытом состоянии капкан не представляет опасности.
   Если наступить на капкан в открытом состоянии или в состоянии захлапывания, то он нанесет урон и исчезнет. Персонаж и
   враги получают урон, еда - исчезает.
6. Капканы можно подбирать, если они в закрытом состоянии(аккуратно! капкан может открыться). Что бы выкинуть капкан
   нажмите 'T'. Позже его можно опять подобрать. При выкидывании капкана
   он ставится в открытом состоянии по направлению последнего движения.
7. В режиме случайной генерации карт, количество карт бесконечное. В данном режиме количество шагов не ограничено. Вход
   в дверь, переносящую на предыдущий уровень,
   означает выход в главное меню. В HUD отображается текущий уровень подземелья.

### Список дополнительных фичей:

1. В игре питательность еды рассчитывается как длина слова, обозначающего еду, умноженного на коэффициент питательности.
   Например mango: 5 * 3 = 15 шагов.
2. В игре есть хилки. Нажмите на 'R', что бы использовать её.
3. Подробный HUD.