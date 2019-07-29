#pragma once

namespace ChatTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Collections::Generic;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;
	

	/// <summary>
	/// ChatForm에 대한 요약입니다.
	/// </summary>
	public ref class ChatForm : public System::Windows::Forms::Form
	{
	public:
		ChatForm(void)
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
		~ChatForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::TextBox^ txbAddress;

	protected:


	private: System::Windows::Forms::RichTextBox^ mainTextBox;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker;


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
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->txbAddress = (gcnew System::Windows::Forms::TextBox());
			this->mainTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"IP주소 : ";
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(368, 32);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 1;
			this->btnStart->Text = L"시작";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &ChatForm::BtnStart_Click);
			// 
			// txbAddress
			// 
			this->txbAddress->Location = System::Drawing::Point(83, 33);
			this->txbAddress->Name = L"txbAddress";
			this->txbAddress->Size = System::Drawing::Size(279, 25);
			this->txbAddress->TabIndex = 2;
			// 
			// mainTextBox
			// 
			this->mainTextBox->Location = System::Drawing::Point(15, 65);
			this->mainTextBox->Name = L"mainTextBox";
			this->mainTextBox->Size = System::Drawing::Size(444, 315);
			this->mainTextBox->TabIndex = 3;
			this->mainTextBox->Text = L"";
			this->mainTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ChatForm::MainTextBox_KeyPress);
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ChatForm::BackgroundWorker_DoWork);
			// 
			// ChatForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(471, 407);
			this->Controls->Add(this->mainTextBox);
			this->Controls->Add(this->txbAddress);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->label1);
			this->Name = L"ChatForm";
			this->Text = L"ServerForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ChatForm::ChatForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &ChatForm::ChatForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	public: static Socket^ server;
	public: static List<Socket^>^ listClient = gcnew List<Socket^>();
	public: static IPEndPoint^ IP;
	public: static Thread^ threadClient;


			// 결과 텍스트 박스 수정불가 
	private: System::Void MainTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = true;
	}

			 // 버튼을 클릭하면 아이피설정, 비동기 실행 , 포트 : 2016
	private: System::Void BtnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		IP = gcnew IPEndPoint(IPAddress::Parse(txbAddress->Text), 2016);
		backgroundWorker->WorkerSupportsCancellation = true;
		backgroundWorker->RunWorkerAsync();
	}

			 // 로드되면 서버소켓 초기화
	private: System::Void ChatForm_Load(System::Object^ sender, System::EventArgs^ e) {
		server = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::IP);
	}
	private: System::Void BackgroundWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		
		// 서버 동작을 알림
		server->Bind(IP);
		server->Listen(10);
		String^ text = "서버가 동작하고 있습니다.";
		System::Drawing::Font^ font = gcnew System::Drawing::Font("맑은 고딕", 9, FontStyle::Bold);
		System::Drawing::Color^ color = Color::Red;
		addTextToMainTextBox(text, font, color);

		// 무한 반복으로 사용자들을 컨트롤함
		while (true)
		{
			Socket^ clientAccept = server->Accept();
			listClient->Add(clientAccept);

			// 클라이언트 접속 시 해당 클라이언트만의 쓰레드를 할당해 client 함수 시작
			threadClient = gcnew Thread(gcnew ParameterizedThreadStart(ChatTest::ChatForm::Client));
			threadClient->IsBackground = true;
			threadClient->Start(clientAccept);

			// 클라이언트 접속을 알림
			String^ textTemp = "클라이언트가 접속했습니다." + clientAccept->RemoteEndPoint->ToString();
			System::Drawing::Font^ fontTemp = gcnew System::Drawing::Font("맑은 고딕", 9, FontStyle::Bold);
			System::Drawing::Color^ colorTemp = Color::Blue;
			addTextToMainTextBox(textTemp, fontTemp, colorTemp);
		}
	}

			 //하나의 클라이언트를 다루는 쓰레드 함수 
	private: static void Client(Object^ obj)
	{
		Socket^ socket = (Socket^)obj;
		while (true)
		{
			try {
				//클라이언트에게서 버퍼를 통해 메시지를 입력	
				array<unsigned char>^ buff = gcnew array<unsigned char>(1024);
				int temp = socket->Receive(buff);

				//모든 클라이언트에게 해당 메시지를 전송
				for each (Socket ^ sock in listClient)
				{
					try
					{
						sock->Send(buff, buff->Length, SocketFlags::None);
					}
					catch (Exception^ exception)
					{
						
					}
				}
			}
			// 오류가 발생한경우 해당 클라이언트 소켓 삭제
			catch (Exception^ exception)
			{
				listClient->Remove(socket);
				return;
			}

		}
	}

			 // 결과 텍스트 박스에 텍스트를 쓰는 함수 
	private: void addTextToMainTextBox(String^ text, System::Drawing::Font^ font, System::Drawing::Color^ color)
	{
		mainTextBox->SelectionFont = font;
		mainTextBox->SelectionColor = (Color)color;
		mainTextBox->AppendText(text + "\n");
	}

	private: System::Void ChatForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		if (backgroundWorker->IsBusy)
		{
			backgroundWorker->CancelAsync();
		}
	}
};
}
