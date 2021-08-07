#include <iostream>
#include <string>    // для std::string
#include <clocale>   // для вывода сообщений на кириллице 
#include <vector>

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
		if (face)
		{
			// значение - это число, указанное на карте
			value = m_rank;
			// значение равно 10 для JACK, QUEEN и KING
			if (value > 10)
				value = 10;
		}
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
		if (cards_on_hand[0]->getCardValue() == 0)
			return 0;

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
	Player(const string& name = "");

	virtual ~Player();

	// показывает, хочет ли игрок продолжать брать карты
	virtual bool IsHitting() const;

	// объявляет, что игрок победил
	void Win() const;

	// объявляет, что игрок проиграл
	void Lose() const;

	// объявляет ничью
	void Push() const;
};

bool Player::IsHitting() const
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
	House(const string& name = "House");

	virtual ~House();

	// показывает, хочет ли дилер продолжать брать карты
	virtual bool IsHitting() const;

	// переворачивает первую карту
	void FlipFirstCard();
};

bool House::IsHitting() const
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

int main()
{
	// для вывода сообщений пользователю на кириллице
	setlocale(LC_CTYPE, "rus");

	Card c1(Card::Spades, Card::rank8, true);
	cout << c1.printCard() << endl;

	Card c2(Card::Clubs, Card::Queen);
	cout << c2.printCard() << endl;

	Card c3(Card::Clubs, Card::Ace);
	cout << c3.printCard() << endl;

	Card c4(Card::Spades, Card::Ace, true);
	cout << c4.printCard() << endl;

	Card c5(Card::Hearts, Card::Ace, true);
	cout << c5.printCard() << endl;

	Hand someHand;
	someHand.Add(&c1);
	someHand.Add(&c2);
	someHand.Add(&c3);
	someHand.Add(&c4);
	someHand.Add(&c5);
	std::cout << "Summ value on hand: " << someHand.GetValue() << std::endl;
	someHand.Clear();

	// main из методички:
	//cout << "\t\tWelcome to Blackjack!\n\n";

	//int numPlayers = 0;
	//while (numPlayers < 1 || numPlayers > 7)
	//{
	//	cout << "How many players? (1 - 7): ";
	//	cin >> numPlayers;
	//}

	//vector<string> names;
	//string name;
	//for (int i = 0; i < numPlayers; ++i)
	//{
	//	cout << "Enter player name: ";
	//	cin >> name;
	//	names.push_back(name);
	//}
	//cout << endl;

	//// игровой цикл
	//Game aGame(names);
	//char again = 'y';
	//while (again != 'n' && again != 'N')
	//{
	//	aGame.Play();
	//	cout << "\nDo you want to play again? (Y/N): ";
	//	cin >> again;
	//}

	return 0;
}