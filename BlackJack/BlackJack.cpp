#include <iostream>
#include <string>    // для std::string
#include <clocale>   // для вывода сообщений на кириллице 
#include <vector>
#include <algorithm>
#include <ctime>     // чтобы в randomize опираться на время запуска программы

using std::cout; using std::endl; using std::cin;
using std::string;

class Card
{
public:
	//перечисление мастей
	enum Suits
	{
		Diamonds, //буби
		Hearts,   //черви
		Spades,   //пики
		Clubs,    //крести
		suitsNumber //для обозначения количества мастей
	};

	//перечисление достоинств карт
	enum CardRanks
	{

		Ace = 1,
		rank2,
		rank3,
		rank4,
		rank5,
		rank6,
		rank7,
		rank8,
		rank9,
		rank10,
		Jack,
		Queen,
		King,
		//Jocker,
		ranksNumber //для обозначения количества достоинств
	};
private:
	//переменные для представления карты
	Suits m_suit;
	CardRanks m_rank;
	bool face;        // true, если карту видно
public:
	//конструктор класса Card с инициализацией карт (переменных-членов класса)
	Card(Suits suit = suitsNumber, CardRanks rank = ranksNumber, bool visible = false) : m_suit(suit), m_rank(rank), face(visible)
	{}

	//printCard функция возвращает принимаемую как параметр карту в виде строки типа ДостоинствоМасть
	string printCard() const
	{
		string cardCode{};

		//сначала разбираемся с достоинствами карты
		switch (m_rank)
		{
		case rank2:
			cardCode = "2";
			break;
		case rank3:
			cardCode = "3";
			break;
		case rank4:
			cardCode = "4";
			break;
		case rank5:
			cardCode = "5";
			break;
		case rank6:
			cardCode = "6";
			break;
		case rank7:
			cardCode = "7";
			break;
		case rank8:
			cardCode = "8";
			break;
		case rank9:
			cardCode = "9";
			break;
		case rank10:
			cardCode = "10";
			break;
		case Jack:
			cardCode = "Валет";
			break;
		case Queen:
			cardCode = "Дама";
			break;
		case King:
			cardCode = "Kороль";
			break;
		case Ace:
			cardCode = "Туз";
			break;
		default:
			cardCode = "ErrorRank";
		}

		//теперь добавляем в строку масть
		switch (m_suit)
		{
		case Diamonds: //буби
			cardCode += "Буби";
			break;
		case Hearts:   //черви
			cardCode += "Черви";
			break;
		case Spades:   //пики
			cardCode += "Пики";
			break;
		case Clubs:    //крести
			cardCode += "Крести";
			break;
		default:
			cardCode += "ErrorSuit";
		}
		return cardCode;
	}

	//getCardValue возвращает значение карты (валет, королева или король — это 10, туз — это 11)
	unsigned short getCardValue() const
	{
		int value = 0;
		//if (face)
		//{
			// значение - это число, указанное на карте
			value = m_rank;
			// значение равно 10 для JACK, QUEEN и KING
			if (value > 10)
				value = 10;
         //}

		return value;
	}
	// переворачивает карту, т.е. если она была рубашкой вверх, то поворачивает лицом вверх, и наоборот
	void flip()
	{
		face = !face;
	}

	bool is_Ace() const
	{
		return (m_rank == Ace) ? true : false;
	}

	friend std::ostream& operator<<(std::ostream& os, const Card& aCard);
};

// перегружает оператор <<, чтобы получить возможность отправить объект типа Card в поток cout
std::ostream& operator<<(std::ostream& os, const Card& aCard)
{
	const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
	const string SUITS[] = { "c", "d", "h", "s" };

	if (aCard.face)
		os << RANKS[aCard.m_rank] << SUITS[aCard.m_suit];
	else
		os << "XX";

	return os;
}

class Hand
{
protected:
	std::vector <Card*> cards_on_hand;
public:
	Hand() 
	{
		cards_on_hand.reserve(7);
	}
	// виртуальный деструктор
	virtual ~Hand()
	{
		Clear();
	}
	// добавляет в коллекцию карт новую карту
	void Add(Card* card)
	{
		cards_on_hand.push_back(card);
	}
	// очищает руку от карт
	void Clear()
	{
		// вызывает runtime error (Debug Assertion Failed):
		/*
		for (auto card_ptr : cards_on_hand)
		{
			delete card_ptr;
			card_ptr = nullptr;
		}
		*/
		cards_on_hand.clear();
	}
	// возвращает сумму очков карт руки
	unsigned short GetValue() const
	{
		if (cards_on_hand.empty())
			return 0;

		//если первая карта имеет значение 0, то она лежит рубашкой вверх:
        // вернуть значение 0
		//if (cards_on_hand[0]->getCardValue() == 0)
		//	return 0;

		unsigned short summ{ 0 };
		size_t aces_on_hand{ 0 };
		for (const auto& card_ptr : cards_on_hand)
		{
			summ += card_ptr->getCardValue();
			if (card_ptr->is_Ace())
				++aces_on_hand;
		}

		const int goal{ 21 };
		//считаем тузы как 11 вместо 1, если сумма меньше 11:
		while ((summ <= (goal-10)) && (aces_on_hand > 0))
		{
			summ += 10;
			--aces_on_hand;
		}

		return summ;
	}
};

class GenericPlayer : public Hand
{
protected:
	string m_name;
public:
	GenericPlayer(const string& name_of_player = ""): m_name{name_of_player} {}
	virtual ~GenericPlayer() {}
	// возвращает информацию, нужна ли игроку еще одна карта
	virtual bool isHitting() const = 0;
	// возвращает bool значение, есть ли у игрока перебор
	bool isBoosted() const
	{
		const int goal{ 21 };
		return (GetValue() > goal) ? true : false;
	}
	// выводит на экран имя игрока и объявляет, что у него перебор
	void Bust() const
	{
		if (isBoosted())
			cout << "У игрока " << m_name << " перебор!\n";
	}
	friend std::ostream& operator<<(std::ostream&, const GenericPlayer&);
};

std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer)
{
	os << aGenericPlayer.m_name << ":\t";

	std::vector<Card*>::const_iterator pCard;
	if (!aGenericPlayer.cards_on_hand.empty())
	{
		for (const auto pCard: aGenericPlayer.cards_on_hand)
			os << *pCard << "\t";

		if (aGenericPlayer.GetValue() != 0)
			cout << "(" << aGenericPlayer.GetValue() << ")";
	}
	else
		os << "<empty>";

	return os;
}

class Player : public GenericPlayer
{
public:
	Player(const string& name = ""): GenericPlayer(name) {}

	virtual ~Player() {}

	// показывает, хочет ли игрок продолжать брать карты
	bool isHitting() const override;

	// объявляет, что игрок победил
	void Win() const;

	// объявляет, что игрок проиграл
	void Lose() const;

	// объявляет ничью
	void Push() const;
};

bool Player::isHitting() const
{
	cout << m_name << ", хотите взять ещё одну карту? (Y/N): ";
	char response;
	cin >> response;
	return (response == 'y' || response == 'Y');
}

void Player::Win() const
{
	cout << "Игрок " << m_name << " выиграл!\n";
}

void Player::Lose() const
{
	cout << "Игрок " << m_name << " проиграл.\n";
}

void Player::Push() const
{
	cout << "Игрок " << m_name << " сыграл вничью.\n";
}

class House : public GenericPlayer
{
private:
	int limit = 16;
public:
	House(const string& name = "House"): GenericPlayer(name) {}

	virtual ~House() {}

	// показывает, хочет ли дилер продолжать брать карты
	bool isHitting() const override;

	// переворачивает первую карту
	void FlipFirstCard();
};

bool House::isHitting() const
{
	return (GetValue() <= limit);
}

void House::FlipFirstCard()
{
	if (!(cards_on_hand.empty()))
		cards_on_hand[0]->flip();
	else
		cout << "Нет карт, которые можно перевернуть!\n";
}

class Deck : public Hand
{
public:
	Deck();

	virtual ~Deck();

	// создает стандартную колоду из 52 карт
	void Populate();

	// тасует карты
	void Shuffle();

	// раздает одну карту в руку
	void Deal(Hand& aHand);

	// дает дополнительные карты игроку
	void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck()
{
	cards_on_hand.reserve(52);
	Populate();
}

Deck::~Deck()
{}

void Deck::Populate()
{
	Clear();
	// создает стандартную колоду
	for (int s = Card::Diamonds; s < Card::suitsNumber; ++s)
	{
		for (int r = Card::Ace; r < Card::ranksNumber; ++r)
		{
			Add(new Card(static_cast<Card::Suits>(s), static_cast<Card::CardRanks>(r)));
		}
	}
}

void Deck::Shuffle()
{
	std::random_shuffle(cards_on_hand.begin(), cards_on_hand.end());
}

void Deck::Deal(Hand& aHand)
{
	if (!cards_on_hand.empty())
	{
		aHand.Add(cards_on_hand.back());
		cards_on_hand.pop_back();
	}
	else
	{
		cout << "Колода пуста, раздача невозможна\n";
	}
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
	cout << endl;
	// продолжает раздавать карты до тех пор, пока у игрока не случается
	// перебор или пока он хочет взять еще одну карту
	while (!(aGenericPlayer.isBoosted()) && aGenericPlayer.isHitting())
	{
		Deal(aGenericPlayer);
		cout << aGenericPlayer << endl;

		if (aGenericPlayer.isBoosted())
		{
			aGenericPlayer.Bust();
		}
	}
}

class Game
{
public:
	Game(const std::vector<string>& names);

	~Game();

	// проводит игру в Blackjack
	void Play();

private:
	Deck m_Deck;
	House m_House;
	std::vector<Player> m_Players;
};


// Конструктор этого класса принимает ссылку на вектор строк, представляющих
// имена игроков-людей. Конструктор создает объект класса Player для каждого имени
Game::Game(const std::vector<string>& names)
{
	// создает вектор игроков из вектора с именами
	std::vector<string>::const_iterator pName;
	for (pName = names.begin(); pName != names.end(); ++pName)
	{
		m_Players.push_back(Player(*pName));
	}

	// запускает генератор случайных чисел
	srand(static_cast<unsigned int>(time(0)));
	m_Deck.Populate();
	m_Deck.Shuffle();
}

Game::~Game()
{}

void Game::Play()
{
	// раздает каждому по две стартовые карты
	std::vector<Player>::iterator pPlayer;
	for (int i = 0; i < 2; ++i)
	{
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			m_Deck.Deal(*pPlayer);
		}
		m_Deck.Deal(m_House);
	}

	// прячет первую карту дилера
	m_House.FlipFirstCard();

	// открывает руки всех игроков
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
	{
		cout << *pPlayer << endl;
	}
	cout << m_House << endl;

	// раздает игрокам дополнительные карты
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
	{
		m_Deck.AdditionalCards(*pPlayer);
	}

	// показывает первую карту дилера
	m_House.FlipFirstCard();
	cout << endl << m_House;

	// раздает дилеру дополнительные карты
	m_Deck.AdditionalCards(m_House);

	if (m_House.isBoosted())
	{
		// все, кто остался в игре, побеждают
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			if (!(pPlayer->isBoosted()))
			{
				pPlayer->Win();
			}
		}
	}
	else
	{
		// сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
			++pPlayer)
		{
			if (!(pPlayer->isBoosted()))
			{
				if (pPlayer->GetValue() > m_House.GetValue())
				{
					pPlayer->Win();
				}
				else if (pPlayer->GetValue() < m_House.GetValue())
				{
					pPlayer->Lose();
				}
				else
				{
					pPlayer->Push();
				}
			}
		}

	}

	// очищает руки всех игроков
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
	{
		pPlayer->Clear();
	}
	m_House.Clear();
}

int main()
{
	// для вывода сообщений пользователю на кириллице
	setlocale(LC_CTYPE, "rus");

	// main из методички:
	cout << "\t\tДОБРО ПОЖАЛОВАТЬ В ИГРУ BLACK JACK!\n\n";

	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		cout << "Введите количество игроков (1 - 7): ";
		cin >> numPlayers;
	}

	std::vector<string> names;
	string name;
	for (int i = 0; i < numPlayers; ++i)
	{
		cout << "Имя " << i+1 << "-ого игрока: ";
	    cin >> name;
		names.push_back(name);
	}
	cout << endl;

	// игровой цикл
	Game game(names);
	char again = 'Y';
	while (again != 'n' && again != 'N')
	{
		game.Play();
		cout << "\nХотите сыграть ещё раз? (Y/N): ";
		cin >> again;
	}

	return 0;
}