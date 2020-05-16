# Клиентская часть проекта "Морской бой".

## Документация
Swagger JSON API: https://app.swaggerhub.com/apis/rufa-a/APISeaBattle/1.0.0-oas3

UML-диаграмма классов: 

![image info](docs/client-uml.png)

Схема алгоритма логики работы клиентской части:

![image info](docs/ClientAlg.png)

Вместо POST, PUT, GET HTTP запросов используется TCP-сокет для передачи структуры данных, в которой роут и тип запроса указаны в дополнительной переменной (см. `struct DataRequest`/`struct DataResponse` и `enum Route`).

## Особенности
  - MVC-архитектура 
      - контроллеры: 
        - MenuController
        - AuthController
        - GameController
      - модели:
        - UserModel
        - GameModel
      - представление:
        - GameView
  - Асинхронная работа с сетью
      - библиотека boost: https://github.com/boostorg/boost
      - TCP сокет
      
### Пример      
Например, регистрация пользователя:
  
   1. В объекте `GameClient` вызывается метод `run` с бесконечным циклом, который завершается при выходе из игры или при отключении соединения.
   2. В цикле выбирается определенный контроллер в зависимости от возвращаемой команды пользователя. 
   3. При идентификации вызывается метод `Action` объекта `AuthController`. 
   4. В методе производится выбор регистрации или авторизации (метод `ReadCommand`). 
   5. Далее вызывается `ReadAuthData`, который возвращается введенные данные. 
   6. В методе вызывается `CheckUserAuth` объекта `UserValidator`, который возвращает, правильно ли были введены данные.
   7. Вызывается метод `PostSignup` объекта модели `UserModel`. 
   8. Проводится сериализация данных в объекте `Serializer`, где вызываются методы `Serializer` для сериализации данных и `GetSerializedData` для возврата этих данных.
   9. Вызывается метод `run` объекта `NetworkClient`. В методе производится серия асинхронных вызовов сопоставления доменного имени и IP-адреса, соединения с сетью, отправки данных и чтения полученных данных, после чего вызывается функция отбратного вызова, которая была передана по ссылке для записи данных в существующий объект модели `UserModel`. Десериализируются полученные данные объектом `Serializer`. Десериализованные данные записываются в модель.
   10. После регистрации метод объекта `AuthController` возвращает команду для выбора меню контроллера.
   11. Вызыватеся метод `Action` объекта `MenuController` и т.д.
   
 ### Логика клиента с точки зрения запрос-ответ:
 
 >> клиент делает коннект -> регистрация или вход -> создание или подключение к сессии(игровой комнате) по id (я так рассчитывал, просто удобнее будет мне сделать) -> старт игры (структура пользовательской карты?)  -> делает шаг
 
 Запускается клиент.
 
 [Авторизация/Регистрация]
 
 Пользователю предлагается пройти авторизацию или регистрацию.
 - Пользователь ввел логин и пароль.
 - Инициализируется структура данных `DataRequest`
     - `route = Route::POST_SIGN_IN`
     - Инициализируется структура данных `AuthData`
         - `login = “login”` (введенный пользователем логин)
         - `password = “password”` (введенный пользователем пароль)
     - (Остальные поля по умолчанию)
 - `DataRequest` сериализируется в массив байт
 - Клиент отправляет массив байт на сервер.
 - Сервер получает этот массив байт.
 - Сервер десериализирует массив байт.
 - Инициализируется структура данных `DataResponse`
     - `route = Route::POST_SIGN_IN`
     - Инициализируется структура данных `UserData`
         - `user_id = 1` 
     - (Остальные поля по умолчанию)
 - `DataResponse` сериализируется в массив байт
 - Сервер отправляет массив байт на клиент.
 - Клиент получает этот массив байт.
 - Клиент десериализирует массив байт.
 - Клиент сохраняет `user_id` в модель пользователя.
 
 [Мультиплеер]
 
 После успешной авторизации/регистрации происходит переход основное меню.
 Пользователь выбирает один из 3 вариантов (Single play, Load play, Multi play).
 Мультиплеер:
 - Пользователь вводит карту.
 - Инициализируется структура данных `DataRequest`
     - `route = Route::POST_GAME_START`
     - Инициализируется структура данных `PlayerMapToStart`
         - `player_mode = GameModes::MULTI_MODE` (выбранный пользователем режим игры)
         - Инициализируется структура данных `PlayerMap`
             - `std::map<size_t, ShipCoordinates> ships = = ...` (введенная пользователем карта)
     - (Остальные поля по умолчанию)
 - `DataRequest` сериализируется в массив байт
 - Клиент отправляет массив байт на сервер.
 - Сервер получает этот массив байт.
 - Сервер десериализирует массив байт.
 - Сервер отдает идентификатор игровой сессии.
 - Инициализируется структура данных `DataResponse`
     - `route = Route::POST_GAME_START`
     - Инициализируется структура данных `GameData`
         - `game_id = 1` 
     - (Остальные поля по умолчанию)
 - `DataResponse` сериализируется в массив байт
 - Сервер отправляет массив байт на клиент.
 - Клиент получает этот массив байт.
 - Клиент десериализирует массив байт.
 - Клиент сохраняет `game_id` в модель игры.
 - Сервер ожидает очередного игрока для включения его в эту сессию.
 - Пользователь ожидает противника: раз в 5 секунд отсылает запрос на проверку статуса игровой сессии (был ли найден оппонент?).
 - Инициализируется структура данных `DataRequest`
     - `route = Route::GET_GAME_STATE`
     - Инициализируется структура данных `UserData`
         - `user_id = 1` 
     - Инициализируется структура данных `GameData`
         - `game_id = 1`
     - (Остальные поля по умолчанию)
 - `DataRequest` сериализируется в массив байт
 - Клиент отправляет массив байт на сервер.
 - Сервер получает этот массив байт.
 - Сервер десериализирует массив байт.
 - Инициализируется структура данных `DataResponse`
     - `route = Route::GET_GAME_STATE`
     - Инициализируется структура данных `GameSessionStatus`
         - `status_game_id = GameStatus::GAME_WAIT`
         - `status_play_user = PlayStatus::PLAY_GO`
     - (Остальные поля по умолчанию)
 - `DataResponse` сериализируется в массив байт
 - Сервер отправляет массив байт на клиент.
 - Клиент получает этот массив байт.
 - Клиент десериализирует массив байт.
 - Клиент повторяет запрос через 5 секунд.
 - Если `status_game_id = GameStatus::GAME_START` и `status_play_user = PlayStatus::PLAY_GO`, пользователь делает ход.
 - Инициализируется структура данных `DataRequest`
     - `route = Route::POST_GAME_STEP`
     - Инициализируется структура данных `UserData`
         - `user_id = 1` 
     - Инициализируется структура данных `GameData`
         - `game_id = 1`
     - Инициализируется структура данных `UserStep`
         - Инициализируется структура данных `UserStep`
             - `x = 1`
             - `y = 1`
     - (Остальные поля по умолчанию)
 - `DataRequest` сериализируется в массив байт
 - Клиент отправляет массив байт на сервер.
 - Сервер получает этот массив байт.
 - Сервер десериализирует массив байт.
 - Инициализируется структура данных `DataResponse`
     - `route = Route::POST_GAME_STEP`
     - Инициализируется структура данных `GameStepStatus`
         - `…` (см. `data.h`)
     - (Остальные поля по умолчанию)
 - `DataResponse` сериализируется в массив байт
 - Сервер отправляет массив байт на клиент.
 - Клиент получает этот массив байт.
 - Клиент десериализирует массив байт.
 - Клиент получил результат своего шага.
 - Клиент раз в 5 секунд опрашивает результат хода противника.
 - Инициализируется структура данных `DataRequest`
     - `route = Route::GET_GAME_STEP`
     - Инициализируется структура данных `UserData`
         - `user_id = 1`
     - Инициализируется структура данных `GameData`
         - `game_id = 1`
     - (Остальные поля по умолчанию)
 - `DataRequest` сериализируется в массив байт
 - Клиент отправляет массив байт на сервер.
 - Сервер получает этот массив байт.
 - Сервер десериализирует массив байт.
 - Если противник сделал/не сделал шаг, то формируется ответ как и на `POST_GAME_STEP`, только с результатами хода противника (если он сделал ход)
 - Инициализируется структура данных `DataResponse`
     - `route = Route::GET_GAME_STEP`
     - Инициализируется структура данных `GameStepStatus`
         - … (см. `data.h`)
     - (Остальные поля по умолчанию)
 - `DataResponse` сериализируется в массив байт
 - Сервер отправляет массив байт на клиент.
 - Клиент получает этот массив байт.
 - Клиент десериализирует массив байт.
 - Клиент получил результат шага противника.
 - Если противник походил, то клиент делает шаг. Иначе через 5 секунд повторный опрос.
 ...
 
