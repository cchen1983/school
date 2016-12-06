using System;
using System.Net;
using System.Net.Mail;

namespace DIP
{
	public class EmailMsg:IMsg
	{
		public void Broadcast(String msg) {
			try
			{
				MailAddress from = new MailAddress("ahoustonteppan@gmail.com");
				MailAddress to = new MailAddress("ahoustonteppan@gmail.com");

				string pwd = "Comp5423Fun";
				string title = "ChaoChen-Election Result DIP: " + DateTime.Now.ToString();

				SmtpClient smtp = new SmtpClient();
				smtp.Host = "smtp.gmail.com";
				smtp.Port = 587;
				smtp.EnableSsl = true;
				smtp.DeliveryMethod = SmtpDeliveryMethod.Network;
				smtp.UseDefaultCredentials = false;
				smtp.Credentials = new NetworkCredential(from.Address, pwd);


				MailMessage mail = new MailMessage(from, to);
				mail.Subject = title;
				mail.Body = msg;
				smtp.Send(mail);
				Console.WriteLine("Email sending: " + msg);
			}
			catch (Exception e) {
				throw new DIPException("EmailMsg Error: " + e.Message); 
			}
		}

		public EmailMsg()
		{
		}
	}
}
