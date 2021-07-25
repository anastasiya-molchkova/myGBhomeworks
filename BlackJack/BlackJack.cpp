#include <iostream>
#include <string>    // для std::string
#include <clocale>   // для вывода сообщений на кириллице 

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
		Ace,
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
		switch (m_rank)
		{
		case rank2:
		case rank3:
		case rank4:
		case rank5:
		case rank6:
		case rank7:
		case rank8:
		case rank9:
		case rank10:
			return (m_rank + 2); // двойка имеет 0 индекс в перечислении, 3 - первый и т.д.
		case Jack:
		case Queen:
		case King:
			return 10;
		case Ace:
			return 11;
		default:
			return 0;
		}
	}
	// переворачивает карту, т.е. если она была рубашкой вверх, то поворачивает лицом вверх, и наоборот
	void flip()
	{
		face = !face;
	}
};

int main()
{
	// для вывода сообщений пользователю на кириллице
	setlocale(LC_CTYPE, "rus");

	Card c1(Card::Spades, Card::rank8, true);
	cout << c1.printCard() << endl;

	Card c2(Card::Clubs, Card::Queen);
	cout << c2.printCard() << endl;

	return 0;
}