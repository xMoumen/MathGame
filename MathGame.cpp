#include <iostream>
using namespace std;

enum enOpLevel { Easy = 1, Mid = 2, Hard = 3, LevelMix = 4 };

enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, TypeMix = 5 };

struct stQuestion
{
	short Num1 = 0, Num2 = 0;
	short Answer = 0;
	short CorrectAnswer = 0;
	enOpLevel OpLevel;
	enOpType OpType;
	bool AnswerResult = 0;
};

struct stQuizz
{
	short NumOfQuestions = 0;
	stQuestion Question[100];
	enOpLevel QuizzLevel;
	enOpType QuizzOpType;
	short CorrectAnswers = 0;
	short WrongAnswers = 0;
	bool isPass = 0;
};

int RandomNumber(int From, int To)
{
	int RandomNum = rand() % (To - From + 1) + From;

	return RandomNum;
}

short ReadHowManyQuestions()
{
	short QuestionsNum = 0;
	do
	{
		cout << "Please enter how many questions:  ";
		cin >> QuestionsNum;
	} while (QuestionsNum < 1 || QuestionsNum > 10);

	return QuestionsNum;
}

enOpType ReadOperationsType()
{
	short Type = 0;
	do
	{
		cout << "Please enter operation type: [1]: Add, [2]: Sub,";
		cout << " [3]: Mul, [4]: Div, [5]: Mix  ";
		cin >> Type;
		cout << "\n";
	} while (Type < 1 || Type > 5);

	return enOpType(Type);
}

enOpLevel ReadOperationsLevel()
{
	short Level = 0;
	do
	{
		cout << "Please enter operation level: [1]: Easy, [2]: Mid,";
		cout << " [3]: Hard, [4]: Mix  ";
		cin >> Level;
	} while (Level < 1 || Level > 4);

	return enOpLevel(Level);
}

short ReadAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}

enOpType GetRandomType()
{
	int Type = RandomNumber(1, 4);
	return enOpType(Type);
}

string GetOpLevelName(enOpLevel Level)
{
	string arrLevelName[4] = { "Easy", "Mid", "Hard", "Mix" };
	return arrLevelName[Level - 1];
}

string GetOpTypeName(enOpType Type)
{
	string arrLevelName[5] = { "+", "-", "*", "/", "Mix" };
	return arrLevelName[Type - 1];
}

short CorrectAnswer(short Num1, short Num2, enOpType Type)
{
	switch (Type)
	{
	case Add:
		return Num1 + Num2;
	case Sub:
		return Num1 - Num2;
	case Mul:
		return Num1 * Num2;
	case Div:
		return Num1 / Num2;
	}
}

stQuestion GenerateQuestion(enOpLevel Level, enOpType Type)
{
	stQuestion Question;

	if (Level == LevelMix)
	{
		Level = enOpLevel(RandomNumber(1, 3));
	}

	if (Type == TypeMix)
	{
		Type = GetRandomType();
	}
	
	Question.OpType = Type;

	switch (Level)
	{
	case Easy:
		Question.Num1 = RandomNumber(1, 10);
		Question.Num2 = RandomNumber(1, 10);

		Question.CorrectAnswer = CorrectAnswer(Question.Num1, Question.Num2, Type);
		Question.OpLevel = Level;
		break;
	case Mid:
		Question.Num1 = RandomNumber(10, 50);
		Question.Num2 = RandomNumber(10, 50);

		Question.CorrectAnswer = CorrectAnswer(Question.Num1, Question.Num2, Type);
		Question.OpLevel = Level;
		break;
	case Hard:
		Question.Num1 = RandomNumber(50, 100);
		Question.Num2 = RandomNumber(50, 100);

		Question.CorrectAnswer = CorrectAnswer(Question.Num1, Question.Num2, Type);
		Question.OpLevel = Level;
		break;

	}

	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short QuestNum = 0; QuestNum < Quizz.NumOfQuestions; QuestNum++)
	{
		Quizz.Question[QuestNum] = GenerateQuestion(Quizz.QuizzLevel, Quizz.QuizzOpType);
	}
}

void PrintQuestions(stQuizz Quizz, short QuestionNumber)
{
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumOfQuestions << "]\n\n";
	cout << Quizz.Question[QuestionNumber].Num1 << "\n";
	cout << Quizz.Question[QuestionNumber].Num2 << " ";
	cout << GetOpTypeName(Quizz.Question[QuestionNumber].OpType);
	cout << "\n-------------\n";
}

void SetScreenColor(bool isCorrect)
{
	if (isCorrect)
		system("color 2F");
	else
		system("color 4F");
}

void CorrectAnswer(stQuizz &Quizz, short QuestionNum)
{
	if (Quizz.Question[QuestionNum].Answer != Quizz.Question[QuestionNum].CorrectAnswer)
	{
		Quizz.WrongAnswers++;
		cout << "\nWrong Answer :(\n";
		cout << "Right answer is : " << Quizz.Question[QuestionNum].CorrectAnswer << "\n\n";
		Quizz.Question[QuestionNum].AnswerResult = 0;
	}
	else
	{
		Quizz.CorrectAnswers++;
		cout << "\nRight Answer :)\n\n";
		Quizz.Question[QuestionNum].AnswerResult = 1;
	}

	SetScreenColor(Quizz.Question[QuestionNum].AnswerResult);
}

void AskAndCorrectAnswers(stQuizz &Quizz)
{
	for (short QuestNum = 0; QuestNum < Quizz.NumOfQuestions; QuestNum++)
	{
		PrintQuestions(Quizz, QuestNum);
		Quizz.Question[QuestNum].Answer = ReadAnswer();
		CorrectAnswer(Quizz, QuestNum);
	}

	Quizz.isPass = (Quizz.CorrectAnswers >= Quizz.WrongAnswers);
}

string PrintPassOrFail(bool IsPass)
{
	if (IsPass)
		return "PASS";
	else
		return "FAIL";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "-------------------------------------" << endl;
	cout << "Final Results is " << PrintPassOrFail(Quizz.isPass) << "\n";
	cout << "-------------------------------------" << "\n\n";
	cout << "Number of Questions: " << Quizz.NumOfQuestions << "\n";
	cout << "Question level : " << GetOpLevelName(Quizz.QuizzLevel) << "\n";
	cout << "Operation type : " << GetOpTypeName(Quizz.QuizzOpType) << "\n";
	cout << "Number of correct answers : " << Quizz.CorrectAnswers << "\n";
	cout << "Number of wrong answers : " << Quizz.WrongAnswers << "\n";
	cout << "-------------------------------------" << "\n\n";
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumOfQuestions = ReadHowManyQuestions();
	Quizz.QuizzLevel = ReadOperationsLevel();
	Quizz.QuizzOpType = ReadOperationsType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayMore = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << "Do you want to play again? Y/N  ";
		cin >> PlayMore;

	} while (PlayMore == 'Y' || PlayMore == 'y');

}

int main()
{
	
	srand((unsigned)time(NULL));

	StartGame();
	

}
