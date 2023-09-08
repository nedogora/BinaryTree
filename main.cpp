#include<iostream>
using namespace std;

#define tab "\t"
#define DELIMITER cout<<"\n//////////////////////////////////////////////////////////////////////\n"
#define CheckInsert
#define Min_Max
#define CheckDelete

class Element
{
	int Data;
	Element* pLeft;
	Element* pRight;

public:
	Element(int Data)
	{
		this->Data = Data;
		pLeft = nullptr;
		pRight = nullptr;

		cout << "EConstructor:" << tab << this << endl;
	}

	~Element()
	{
		cout << "EDestructor:" << tab << this << endl;
	}

	Element* getpLeft()
	{
		return this->pLeft;
	}

	Element* getpRight()
	{
		return this->pRight;
	}

	friend ostream& operator<<(ostream& os, const Element& obj);
	friend class Tree;
};

ostream& operator<<(ostream& os, const Element& obj)
{
	os << obj.Data;
	return os;
}

class Tree
{
	Element* root;

public:
	Tree()
	{
		this->root = nullptr;

		cout << "TConstructor:" << tab << this << endl;
	}

	~Tree()
	{
		this->Clean(this->GetRoot());
		cout << "TDestructor:" << tab << this << endl;
	}

	Element* GetRoot() const
	{
		return this->root;
	}

	void SetRoot(Element* root)
	{
		this->root = root;
	}

	void Insert(Element* root, int Data)
	{
		if (this->root == nullptr)
		{
			this->root = new Element(Data);
			return;
		}

		Element* Temp = root;

		if (Temp->Data > Data)
		{
			if (Temp->pLeft != nullptr) Insert(Temp->pLeft, Data);
			else Temp->pLeft = new Element(Data);
		}
		else
		{
			if (Temp->pRight != nullptr) Insert(Temp->pRight, Data);
			else Temp->pRight = new Element(Data);
		}
	}

	int minValue(Element* root)
	{
		//Element* Temp = root;

		if (root->pLeft) minValue(root->pLeft);
		else return root->Data;

		/*if (Temp->pLeft)
		{
		Temp = Temp->pLeft;
		minValue(Temp);
		}
		else return Temp->Data;*/
	}

	int maxValue(Element* root)
	{
		//Element* Temp = root;

		if (root->pRight) maxValue(root->pRight);
		else return root->Data;

		/*if (Temp->pRight)
		{
		Temp = Temp->pRight;
		maxValue(Temp);
		}
		else return Temp->Data;*/
	}

	/*void Clean(Element* root)
	{
	Element* Temp = root;

	if (this->root->pLeft == nullptr && this->root->pRight == nullptr)
	{
	delete this->root;
	this->root = nullptr;
	return;
	}

	if (Temp->pLeft)
	{
	if (Temp->pLeft->pLeft == Temp->pLeft->pRight)
	{
	delete Temp->pLeft;
	Temp->pLeft = nullptr;
	}
	else Clean(Temp->pLeft);
	Clean(Temp);
	}

	else if (Temp->pRight)
	{
	if (Temp->pRight->pLeft == Temp->pRight->pRight)
	{
	delete Temp->pRight;
	Temp->pRight = nullptr;
	}
	else Clean(Temp->pRight);
	Clean(Temp);
	}
	}*/

	void DelMaxValue(Element* root)
	{
		if (root->pRight->pRight) DelMaxValue(root->pRight);
		else
		{
			delete root->pRight;
			root->pRight = nullptr;
		}
	}

	void DelMinValue(Element* root)
	{
		if (root->pLeft->pLeft) DelMinValue(root->pLeft);
		else
		{
			delete root->pLeft;
			root->pLeft = nullptr;
		}
	}

	/*void Delete(Element* root, int index)
	{
		//if (root == nullptr) return;
		//Element* Temp = root;
		//if (Temp->Data == index)
		//{
		//	if (Temp->pLeft)
		//	{
		//		Temp = this->maxValue(Temp->pLeft);
		//		if (root->pLeft)
		//		{
		//			root->Data = Temp->Data;
		//			delete Temp;
		//			return;
		//			//root->pLeft = Temp->pLeft;
		//			//Temp->pLeft = root;
		//		}
		//		else if (root->pRight)
		//		{
		//			if (root->pRight->Data > Temp->Data)
		//			{
		//				root->pRight->Data = Temp->Data;
		//			}
		//			else
		//			{
		//				Temp = this->minValue(Temp->pRight);
		//				root->pRight->Data = Temp->Data;
		//			}
		//			delete Temp;
		//			return;
		//		}
		//	}
		//	else if (Temp->pRight)
		//	{
		//		Temp = this->minValue(Temp->pRight);
		//		if (root->pRight) Temp->pRight = root->pRight;
		//		if (root->pLeft)
		//		{
		//			if (root->pLeft->Data > Temp->Data) Temp->pRight = root->pLeft;
		//			else Temp->pLeft = root->pRight;
		//		}
		//		delete Temp;
		//		return;
		//	}
		//}
		//Delete(root->pLeft, index);
		////return;
		//Delete(root->pRight, index);
//		if (root == nullptr) return;
//		if (root->Data == index)
//		{
//			if (root->pLeft)
//			{
//				root->Data = this->maxValue(root->pLeft);
//				this->DelMaxValue(root->pLeft);
//			}
//			else if (root->pRight)
//			{
//				root->Data = this->minValue(root->pRight);
//				this->DelMinValue(root->pRight);
//			}
//		}
//		Delete(root->pLeft, index);
//		Delete(root->pRight, index);
	}*/

	void Delete(Element* root, int data)
	{
		if (!root) return;

		Element* Temp;
		while (root)
		{
			if (root->Data > data)
			{
				Temp = root;
				root = root->pLeft;
			}
			else if (root->Data < data)
			{
				Temp = root;
				root = root->pRight;
			}
			else break;
		}

		if (root->pLeft==root->pRight)
		{
			if (Temp->Data < data)Temp->pRight = nullptr;
			else Temp->pLeft = nullptr;
			delete root;
		}
		else if (root->pLeft&&!root->pRight)
		{
			if (Temp->Data < data)Temp->pRight = root->pLeft;
			else Temp->pLeft = root->pLeft;
			delete root;
		}
		else if (!root->pLeft&&root->pRight)
		{
			if (Temp->Data < data)Temp->pRight = root->pRight;
			else Temp->pLeft = root->pRight;
			delete root;
		}
		else
		{
			Element* value = root;
			value = value->pLeft;
			if (!value->pRight)
			{
				if (Temp->Data > data)Temp->pLeft = value;
				else Temp->pRight = value;
				value->pRight = root->pRight;
				delete root;
			}
			else
			{
				Element* preValue;
				while (value->pRight)
				{
					preValue = value;
					value = value->pRight;
				}
				root->Data = value->Data;

				if (!value->pLeft)
				{
					preValue->pRight = nullptr;
					delete value;
				}
				else
				{
					preValue->pRight = value->pLeft;
					delete value;
				}
			}
		}
	}
	void Clean(Element* root)
	{
		if (root == nullptr) return;
		Clean(root->pLeft);
		Clean(root->pRight);
		delete root;
		root = nullptr;
	}

	void Print(Element * root, int node)
	{
		if (root)
		{
			Print(root->pLeft, node + 1);
			//for (int i = 0; i < node; i++) cout << "   ";
			cout << root->Data << endl;
			Print(root->pRight, node + 1);
		}
	}

	/*void Print(Element* root)
	{
	if (root == nullptr) return;
	cout << root->Data <<tab;
	Print(root->pLeft);
	Print(root->pRight);
	}*/
};

void main()
{
	setlocale(LC_ALL, "Rus");

#ifdef CheckInsert

	Tree t1;
	t1.Insert(t1.GetRoot(), 123);
	cout << *t1.GetRoot() << endl;
	t1.Insert(t1.GetRoot(), 58);
	t1.Insert(t1.GetRoot(), 150);
	t1.Insert(t1.GetRoot(), 53);
	t1.Insert(t1.GetRoot(), 65);
	t1.Insert(t1.GetRoot(), 60);
	t1.Insert(t1.GetRoot(), 185);
	t1.Insert(t1.GetRoot(), 55);

	DELIMITER;
	cout << endl;
	t1.Print(t1.GetRoot(), 0);
	//cout << endl;
	DELIMITER;

#endif // CheckInsert

#ifdef Min_Max
	cout << "Min:" << tab << t1.maxValue(t1.GetRoot()->getpLeft()) << endl;
	cout << "Max:" << tab << t1.maxValue(t1.GetRoot()) << endl;


	DELIMITER;
	cout << "Min:" << tab << t1.minValue(t1.GetRoot()) << endl;
	cout << "Max:" << tab << t1.maxValue(t1.GetRoot()) << endl;
	DELIMITER;

#endif // Min_Max

#ifdef CheckDelete
	t1.Delete(t1.GetRoot(), 185);
	t1.Print(t1.GetRoot(), 0);
#endif // CheckDelete

}