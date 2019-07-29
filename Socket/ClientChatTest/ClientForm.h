#pragma once

namespace ClientChatTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Runtime::Serialization;
	using namespace System::Runtime::Serialization::Formatters::Binary;
	using namespace System::Runtime::Serialization::Formatters;
	using namespace System::Threading;

	using namespace FormatterText;
	using namespace System::IO;

	/// <summary>
	/// ClientForm에 대한 요약입니다.
	/// </summary>
	public ref class ClientForm : public System::Windows::Forms::Form
	{
	public:
		ClientForm(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
			CheckForIllegalCrossThreadCalls = false;
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~ClientForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnServerEnter;
	private: System::Windows::Forms::TextBox^ txbIPAddress;
	private: System::Windows::Forms::RichTextBox^ mainTextBox;



	private: System::Windows::Forms::Button^ btnSend;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txbNicname;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker;
	private: System::Windows::Forms::TextBox^ txbInput;
	private: System::Windows::Forms::RichTextBox^ txbUser;
	private: System::Windows::Forms::Label^ label3;


	protected:

	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnServerEnter = (gcnew System::Windows::Forms::Button());
			this->txbIPAddress = (gcnew System::Windows::Forms::TextBox());
			this->mainTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->btnSend = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txbNicname = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->txbInput = (gcnew System::Windows::Forms::TextBox());
			this->txbUser = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"ip주소 :";
			// 
			// btnServerEnter
			// 
			this->btnServerEnter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnServerEnter->Location = System::Drawing::Point(465, 14);
			this->btnServerEnter->Name = L"btnServerEnter";
			this->btnServerEnter->Size = System::Drawing::Size(75, 23);
			this->btnServerEnter->TabIndex = 1;
			this->btnServerEnter->Text = L"접속";
			this->btnServerEnter->UseVisualStyleBackColor = true;
			this->btnServerEnter->Click += gcnew System::EventHandler(this, &ClientForm::BtnServerEnter_Click);
			// 
			// txbIPAddress
			// 
			this->txbIPAddress->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txbIPAddress->Location = System::Drawing::Point(76, 12);
			this->txbIPAddress->Name = L"txbIPAddress";
			this->txbIPAddress->Size = System::Drawing::Size(358, 25);
			this->txbIPAddress->TabIndex = 2;
			// 
			// mainTextBox
			// 
			this->mainTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->mainTextBox->Enabled = false;
			this->mainTextBox->Location = System::Drawing::Point(13, 77);
			this->mainTextBox->Name = L"mainTextBox";
			this->mainTextBox->Size = System::Drawing::Size(421, 328);
			this->mainTextBox->TabIndex = 3;
			this->mainTextBox->Text = L"";
			//this->mainTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientForm::MainTextBox_KeyPress);
			// 
			// btnSend
			// 
			this->btnSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnSend->Location = System::Drawing::Point(465, 423);
			this->btnSend->Name = L"btnSend";
			this->btnSend->Size = System::Drawing::Size(75, 23);
			this->btnSend->TabIndex = 5;
			this->btnSend->Text = L"전송";
			this->btnSend->UseVisualStyleBackColor = true;
			this->btnSend->Click += gcnew System::EventHandler(this, &ClientForm::BtnSend_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(62, 15);
			this->label2->TabIndex = 6;
			this->label2->Text = L"닉네임 :";
			// 
			// txbNicname
			// 
			this->txbNicname->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txbNicname->Location = System::Drawing::Point(77, 46);
			this->txbNicname->Name = L"txbNicname";
			this->txbNicname->Size = System::Drawing::Size(357, 25);
			this->txbNicname->TabIndex = 7;
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ClientForm::BackgroundWorker_DoWork);
			// 
			// txbInput
			// 
			this->txbInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txbInput->Location = System::Drawing::Point(12, 423);
			this->txbInput->Name = L"txbInput";
			this->txbInput->Size = System::Drawing::Size(435, 25);
			this->txbInput->TabIndex = 8;
			this->txbInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientForm::TxbInput_KeyPress_1);
			// 
			// txbUser
			// 
			this->txbUser->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txbUser->Enabled = false;
			this->txbUser->Location = System::Drawing::Point(440, 78);
			this->txbUser->Name = L"txbUser";
			this->txbUser->Size = System::Drawing::Size(104, 327);
			this->txbUser->TabIndex = 9;
			this->txbUser->Text = L"";
			//this->txbUser->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientForm::TxbUser_KeyPress);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(462, 56);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(72, 15);
			this->label3->TabIndex = 10;
			this->label3->Text = L"<접속자>";
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(552, 477);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txbUser);
			this->Controls->Add(this->txbInput);
			this->Controls->Add(this->txbNicname);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btnSend);
			this->Controls->Add(this->mainTextBox);
			this->Controls->Add(this->txbIPAddress);
			this->Controls->Add(this->btnServerEnter);
			this->Controls->Add(this->label1);
			this->Name = L"ClientForm";
			this->Text = L"ClientForm";
			this->Load += gcnew System::EventHandler(this, &ClientForm::ClientForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public: Socket^ client;
	public: IPEndPoint^ IP;
	public: Thread^ clientThread;




	private: System::Void ClientForm_Load(System::Object^ sender, System::EventArgs^ e) {
		client = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::IP);
	}


	private: System::Void BtnServerEnter_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			IP = gcnew IPEndPoint(IPAddress::Parse(txbIPAddress->Text), 2016);
			client->Connect(IP);

			// backgroundWorker1 이벤트 실행
			backgroundWorker->RunWorkerAsync();
		}

		// 오류가 발생한 경우
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
			 // 텍스트 박스에 텍스트를 넣어주는 함수
	private: void addText(String^ text, System::Drawing::Font^ font, System::Drawing::Color^ color)
	{

		// 메인 텍스트 박스에 해당 문자열을 보여줌
		mainTextBox->SelectionFont = font;
		mainTextBox->SelectionColor = (Color)color;
		mainTextBox->AppendText(text + "\n");
		mainTextBox->ScrollToCaret();
	}

	private: void addName(String^ name)
	{

		// 접속자 아이디를 보여줌

		txbUser->AppendText(name + "\n");
		txbUser->ScrollToCaret();
	}

	//private: void deleteName(String^ name)
	//{
	//	// 접속자 아이디를 갱신
	//	txbUser->delete
	//}


	private: System::Void BackgroundWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {


		while (true)
		{

			// 메시지를 버퍼에 담음
			array<unsigned char>^ buf = gcnew array<unsigned char>(1024);
			int temp = client->Receive(buf);
			FormatterText::StructChat^ str = gcnew FormatterText::StructChat();

			// 버퍼로 넘어온 데이터를 FomatterText::StructChat 객체인 str로 변환해 텍스트로 보여줌
			str = Deserialize(buf);
			addText(str->textChat, str->myFont, str->myColor);
			
			if (txbUser->Text->Contains(str->nickname) == false)
			{
				addName(str->nickname);
			}

			/*if (str->nickname->Contains(txbUser->Text) == false)
			{
				deleteName(txbUser->Text);
			}*/
		}
	}

			 // MemoryStream과 BinaryFormatter를 이용해 FormatterText::StructChat의 문자열 형태를 버퍼 형태로 변환하고 다시 원상 복귀 할 수 있음
			 /*public: array<unsigned char, 1> ^ Serialize(FormatterText::StructChat ^ str)
			 {
				 MemoryStream^ ms = gcnew MemoryStream();
				 BinaryFormatter^ bf = gcnew BinaryFormatter();
				 bf->Serialize(ms, str);
				 return ms->ToArray();
			 }*/

	public: FormatterText::StructChat^ Deserialize(array<unsigned char>^ buff)
	{
		MemoryStream^ ms = gcnew MemoryStream(buff);
		BinaryFormatter^ bf = gcnew BinaryFormatter();
		return (FormatterText::StructChat^)bf->Deserialize(ms);
	}

	private: System::Void BtnSend_Click(System::Object^ sender, System::EventArgs^ e) {


		FormatterText::StructChat^ str = gcnew FormatterText::StructChat();

		// 현재의 보낼 문자열을 StructChat 객체 형태로 변환
		if (txbNicname->Text == "")
		{
			txbNicname->Text = "익명";
		}


		str->textChat = txbNicname->Text + " : " + txbInput->Text;
		str->nickname = txbNicname->Text;
		str->myColor = txbInput->ForeColor;
		str->myFont = txbInput->Font;

		// 해당 StructChat 객체 형태를 버퍼로 보낼 수 있게 Serialize() 해서 서버로 보내줌
		array<unsigned char>^ buf = gcnew array<unsigned char>(1024);
		MemoryStream^ ms = gcnew MemoryStream();
		BinaryFormatter^ bf = gcnew BinaryFormatter();
		bf->Serialize(ms, str);
		buf = ms->ToArray();
		client->Send(buf, buf->Length, SocketFlags::None);

		txbInput->Clear();
	}
	/*private: System::Void MainTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = true;
	}


	private: System::Void TxbUser_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = true;
	}*/


	private: System::Void TxbInput_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->SuppressKeyPress)
		{
			this->btnSend->Enabled;
		}
	}

	private: System::Void TxbInput_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == 13)
		{
			this->btnSend->PerformClick();
		}
	}

	};
}

