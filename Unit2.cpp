//---------------------------------------------------------------------------

#include <fmx.h>      //working with the FireMonkey framework
#include <queue>     //   queue container
#pragma hdrstop     //instructs the compiler to stop processing header files after this point, which can improve compilation time.

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)    /*specify the resource file for the form (*.fmx). */
#pragma resource "*.fmx"

class Question {      // These are member variables of the Question class.
public:
    String Text;
    String Answer1;
    String Answer2;
    String Answer3;
	int CorrectAnswer;

	Question() {}        //default constructor for the Question class.
	Question(String text, String ans1, String ans2, String ans3, int correctAns) {
		Text = text;
		Answer1 = ans1;         // represent the text of the three answer choices.
		Answer2 = ans2;
		Answer3 = ans3;
		CorrectAnswer = correctAns;
	}
};

std::queue<Question> LoadQuestions() {
    Question q1 = Question("1.  Which color does not appear on the Olympic rings?", "Black", "Orange", "Green", 2);
    Question q2 = Question("2.  What is the chemical formula for Table Salt?", "NaCl", "NaCl2", "Na2Cl", 1);
    Question q3 = Question("3.  What is the longest river in the world?", "Nile", "Mississippi", "Amazon", 1);
    Question q4 = Question("4.  Who wrote 'Romeo and Juliet'?", "William Shakespeare", "Charles Dickens", "Jane Austen", 1);
    Question q5 = Question("5.  What is the capital of France?", "Berlin", "London", "Paris", 3);
    Question q6 = Question("6.  What is the chemical symbol for gold?", "Ag", "Au", "Fe", 2);
    Question q7 = Question("7.  Which planet is known as the Red Planet?", "Mars", "Venus", "Jupiter", 1);
    Question q8 = Question("8.  Who painted the Mona Lisa?", "Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", 3);
    Question q9 = Question("9.  What is the square root of 81?", "9", "6", "7", 1);
    Question q10 = Question("10.  Which country is known as the Land of the Rising Sun?", "China", "Japan", "India", 2);
    Question q11 = Question("11.  What is the tallest mountain in the world?", "Mount Everest", "K2", "Kangchenjunga", 1);
    Question q12 = Question("12.  What is the largest desert in the world?", "Sahara Desert", "Arabian Desert", "Gobi Desert", 1);
    Question q13 = Question("13.   In which country is the Great Pyramid of Giza located?", "Egypt", "India", "China", 1);
    Question q14 = Question("14.  Who was the first woman to win a Nobel Prize?", "Marie Curie", "Rosalind Franklin", "Mother Teresa", 1);
    Question q15 = Question("15.  What is the largest ocean on Earth?", "Atlantic Ocean", "Indian Ocean", "Pacific Ocean", 3);
    Question q16 = Question("16.  Which famous ship sank on its maiden voyage in 1912?", "HMS Bounty", "SS Great Eastern", "RMS Titanic", 3);
    Question q17 = Question("17.  Which famous scientist developed the theory of general relativity?", "Isaac Newton", "Albert Einstein", "Stephen Hawking", 2);
    Question q18 = Question("18.  Which supercar manufacturer produces the model 'Chiron'?", "Ferrari", "Bugatti", "Lamborghini", 2);
    Question q19 = Question("19.  Who portrays the character Peter Quill, also known as Star-Lord, in the 'Guardians of the Galaxy' films?", "Chris Hemsworth", "Chris Evans", "Chris Pratt", 3);
    Question q20 = Question("20.  Which character famously sang 'Smelly Cat'?", "Phoebe", "Monica", "Rachel", 1);

    std::queue<Question> questions;
    questions.push(q1);
    questions.push(q2);
    questions.push(q3);
    questions.push(q4);
    questions.push(q5);
    questions.push(q6);
    questions.push(q7);
    questions.push(q8);
    questions.push(q9);
    questions.push(q10);
    questions.push(q11);
    questions.push(q12);
    questions.push(q13);
    questions.push(q14);
    questions.push(q15);
    questions.push(q16);
    questions.push(q17);
    questions.push(q18);
    questions.push(q19);
    questions.push(q20);

    return questions;
}

std::queue<Question> questions;        //Queue to hold the questions.
Question currentQuestion;        // Variable to store the current question being displayed.
int selectedAnswer;
int points = 0;         //Variable to keep track of the user's points.

TForm2 *Form2;      // Pointer to the form object.
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)     //Constructor for the specific form (TForm2).
    : TForm(Owner)
{
	questions = LoadQuestions();       //Calls the LoadQuestions function to load the questions into the questions queue.
	currentQuestion = questions.front();  //Retrieves the first question from the queue and stores it in the currentQuestion variable.

	QuestionLabel->Text = currentQuestion.Text;           //display the text of the current question and its answer choices.
    Answer1RadioButton->Text = currentQuestion.Answer1;
	Answer2RadioButton->Text = currentQuestion.Answer2;
	Answer3RadioButton->Text = currentQuestion.Answer3;

	questions.pop();        //Removes the first question from the queue, as it has been displayed.
	PointsLabel->Text = IntToStr(points); // Sets the text property of PointsLabel to display the current points (initialized to 0).
}

//---------------------------------------------------------------------------
void __fastcall TForm2::Answer1RadioButtonChange(TObject *Sender)
{                               //These event handlers
	selectedAnswer = 1;    //are triggered when the user selects an answer by clicking on the corresponding radio button.
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Answer2RadioButtonChange(TObject *Sender)
{
	selectedAnswer = 2;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Answer3RadioButtonChange(TObject *Sender)
{
	selectedAnswer = 3;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::ConfirmButtonClick(TObject *Sender)  // defines the event handler function ConfirmButtonClick for the button click event.
{
	if (selectedAnswer == currentQuestion.CorrectAnswer) {  // checks if the selected answer matches the correct answer for the current question.
		points++;
		PointsLabel->Text = IntToStr(points); // assigns the converted string value to the Text property of the PointsLabel, to show the current value of the points variable.
	} else {
		String correctAnswer;
		switch (currentQuestion.CorrectAnswer) { // switch statement is used to determine which answer among Answer1, Answer2, or Answer3
			case 1:                             //is the correct answer based on the CorrectAnswer attribute of the currentQuestion.
				correctAnswer = currentQuestion.Answer1;
				break;
			case 2:
				correctAnswer = currentQuestion.Answer2;
				break;
			case 3:
				correctAnswer = currentQuestion.Answer3;
				break;
		}
		ShowMessage("Wrong Answer! The correct answer is: " + correctAnswer);
	}

	if (!questions.empty()) {   // checks if the questions queue is not empty.
		currentQuestion = questions.front(); //If the queue is not empty, this line retrieves the first question from the questions queue using the front(),
											// variable will hold the question that is currently being displayed to the user.

		QuestionLabel->Text = currentQuestion.Text; //updated with the text of the question.
		Answer1RadioButton->Text = currentQuestion.Answer1;  //updated with the text of the answer choices.
		Answer2RadioButton->Text = currentQuestion.Answer2;
		Answer3RadioButton->Text = currentQuestion.Answer3;

		questions.pop();   //same question won't be displayed again in the quiz.

		// Uncheck radio buttons, to reset the user's selection for the new question.
		Answer1RadioButton->IsChecked = false;
		Answer2RadioButton->IsChecked = false;
		Answer3RadioButton->IsChecked = false;
	} else {
		ConfirmButton->Enabled = false;
		//disables the ConfirmButton by setting its Enabled property to false.
}      //This prevents the user from attempting to answer more questions when there are none left.
	}
//---------------------------------------------------------------------------

