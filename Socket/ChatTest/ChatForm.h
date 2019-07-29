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
	/// ChatForm�� ���� ����Դϴ�.
	/// </summary>
	public ref class ChatForm : public System::Windows::Forms::Form
	{
	public:
		ChatForm(void)
		{
			InitializeComponent();
			//
			//TODO: ������ �ڵ带 ���⿡ �߰��մϴ�.
			//
			CheckForIllegalCrossThreadCalls = false;
		}

	protected:
		/// <summary>
		/// ��� ���� ��� ���ҽ��� �����մϴ�.
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
		/// �ʼ� �����̳� �����Դϴ�.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����̳� ������ �ʿ��� �޼����Դϴ�. 
		/// �� �޼����� ������ �ڵ� ������� �������� ������.
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
			this->label1->Text = L"IP�ּ� : ";
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(368, 32);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 1;
			this->btnStart->Text = L"����";
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


			// ��� �ؽ�Ʈ �ڽ� �����Ұ� 
	private: System::Void MainTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = true;
	}

			 // ��ư�� Ŭ���ϸ� �����Ǽ���, �񵿱� ���� , ��Ʈ : 2019
	private: System::Void BtnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		IP = gcnew IPEndPoint(IPAddress::Parse(txbAddress->Text), 2019);
		backgroundWorker->WorkerSupportsCancellation = true;
		backgroundWorker->RunWorkerAsync();
	}

			 // �ε�Ǹ� �������� �ʱ�ȭ
	private: System::Void ChatForm_Load(System::Object^ sender, System::EventArgs^ e) {
		server = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::IP);
	}
	private: System::Void BackgroundWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		
		// ���� ������ �˸�
		server->Bind(IP);
		server->Listen(10);
		String^ text = "������ �����ϰ� �ֽ��ϴ�.";
		System::Drawing::Font^ font = gcnew System::Drawing::Font("���� ���", 9, FontStyle::Bold);
		System::Drawing::Color^ color = Color::Red;
		addTextToMainTextBox(text, font, color);

		// ���� �ݺ����� ����ڵ��� ��Ʈ����
		while (true)
		{
			Socket^ clientAccept = server->Accept();
			listClient->Add(clientAccept);

			// Ŭ���̾�Ʈ ���� �� �ش� Ŭ���̾�Ʈ���� �����带 �Ҵ��� client �Լ� ����
			threadClient = gcnew Thread(gcnew ParameterizedThreadStart(ChatTest::ChatForm::Client));
			threadClient->IsBackground = true;
			threadClient->Start(clientAccept);

			// Ŭ���̾�Ʈ ������ �˸�
			String^ textTemp = "Ŭ���̾�Ʈ�� �����߽��ϴ�." + clientAccept->RemoteEndPoint->ToString();
			System::Drawing::Font^ fontTemp = gcnew System::Drawing::Font("���� ���", 9, FontStyle::Bold);
			System::Drawing::Color^ colorTemp = Color::Blue;
			addTextToMainTextBox(textTemp, fontTemp, colorTemp);
		}
	}

			 //�ϳ��� Ŭ���̾�Ʈ�� �ٷ�� ������ �Լ� 
	private: static void Client(Object^ obj)
	{
		Socket^ socket = (Socket^)obj;
		while (true)
		{
			try {
				//Ŭ���̾�Ʈ���Լ� ���۸� ���� �޽����� �Է�	
				array<unsigned char>^ buff = gcnew array<unsigned char>(1024);
				int temp = socket->Receive(buff);

				//��� Ŭ���̾�Ʈ���� �ش� �޽����� ����
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
			// ������ �߻��Ѱ�� �ش� Ŭ���̾�Ʈ ���� ����
			catch (Exception^ exception)
			{
				listClient->Remove(socket);
				return;
			}

		}
	}

			 // ��� �ؽ�Ʈ �ڽ��� �ؽ�Ʈ�� ���� �Լ� 
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
