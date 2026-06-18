import nodemailer from "nodemailer";

const transporter = nodemailer.createTransport({
	host: process.env.EMAIL_SERVER_HOST,
	port: parseInt(process.env.EMAIL_SERVER_PORT || "587"),
	secure: false,
	auth: {
		user: process.env.EMAIL_SERVER_USER,
		pass: process.env.EMAIL_SERVER_PASSWORD,
	},
	logger: true,
	debug: true,
});

export async function sendWelcomeEmail(to: string) {
	if (!process.env.EMAIL_SERVER_USER) {
		console.log("Email server not configured, skipping email to:", to);
		return;
	}

	const mailOptions = {
		from: process.env.EMAIL_FROM,
		to,
		subject: "Welcome to ArtHub",
		text: "Welcome to ArtHub! Your account has been successfully created.",
		html: "<h1>Welcome to ArtHub</h1><p>Your account has been successfully created.</p>",
	};

	await transporter.sendMail(mailOptions);
}

export async function sendVerificationCode(to: string, code: string) {
	console.log("------------------------------------------");
	console.log("VERIFICATION CODE FOR:", to);
	console.log("CODE:", code);
	console.log("------------------------------------------");

	if (!process.env.EMAIL_SERVER_USER) {
		console.log("Email server not configured, skipping actual email send.");
		return;
	}

	const mailOptions = {
		from: process.env.EMAIL_FROM,
		to,
		subject: "Your Verification Code - ArtHub",
		text: `Your verification code is: ${code}. It expires in 15 minutes.`,
		html: `
			<div style="font-family: sans-serif; max-width: 600px; margin: 0 auto; padding: 20px; border: 1px solid #e5e7eb; border-radius: 8px;">
				<div style="text-align: center; margin-bottom: 20px;">
					<img src="cid:logo" alt="ArtHub Logo" style="max-width: 150px; height: auto;" />
				</div>
				<h1 style="color: #111827; text-align: center;">Email Verification</h1>
				<p style="color: #374151; font-size: 16px;">Welcome to ArtHub! Use the code below to verify your email address. It will expire in 15 minutes.</p>
				<div style="background-color: #f3f4f6; padding: 20px; text-align: center; border-radius: 8px; margin: 25px 0;">
					<span style="font-size: 32px; font-weight: bold; letter-spacing: 5px; color: #1d5eff;">${code}</span>
				</div>
				<p style="color: #6b7280; font-size: 14px; text-align: center;">If you didn't request this code, you can safely ignore this email.</p>
			</div>
		`,
		attachments: [
			{
				filename: 'arthub.png',
				path: './assets/arthub.png',
				cid: 'logo'
			}
		]
	};

	try {
		console.log("SMTP Config:", {
			host: process.env.EMAIL_SERVER_HOST,
			port: process.env.EMAIL_SERVER_PORT,
			user: process.env.EMAIL_SERVER_USER
		});
		await transporter.sendMail(mailOptions);
		console.log("SMTP: Actual email sent successfully via Ethereal/SMTP");
	} catch (smtpError) {
		console.error("SMTP ERROR:", smtpError);
	}
}

export async function sendAccountDeletionEmail(to: string, recoveryToken: string) {
	if (!process.env.EMAIL_SERVER_USER) {
		console.log("Email server not configured, skipping deletion email to:", to);
		return;
	}

	const appUrl = process.env.NEXTAUTH_URL || "http://localhost:3000";
	const recoveryLink = `${appUrl}/recover-account?token=${recoveryToken}`;

	const mailOptions = {
		from: process.env.EMAIL_FROM,
		to,
		subject: "ArtHub - Suppression de compte programmée",
		text: `Votre compte ArtHub sera supprimé dans 7 jours. Si vous changez d'avis, utilisez ce lien pour l'annuler : ${recoveryLink}`,
		html: `
			<div style="font-family: sans-serif; max-width: 600px; margin: 0 auto; padding: 20px; border: 1px solid #e5e7eb; border-radius: 8px;">
				<div style="text-align: center; margin-bottom: 20px;">
					<img src="cid:logo" alt="ArtHub Logo" style="max-width: 150px; height: auto;" />
				</div>
				<h1 style="color: #111827; text-align: center;">Suppression Programmée</h1>
				<p style="color: #374151; font-size: 16px;">Bonjour,</p>
				<p style="color: #374151; font-size: 16px;">Vous avez demandé la suppression de votre compte ArtHub. Celui-ci sera définitivement effacé dans 7 jours.</p>
				<p style="color: #374151; font-size: 16px;">Si c'était une erreur ou si vous changez d'avis, vous pouvez annuler cette action en cliquant sur le bouton ci-dessous :</p>
				<div style="text-align: center; margin: 30px 0;">
					<a href="${recoveryLink}" style="background-color: #3b82f6; color: white; padding: 12px 24px; text-decoration: none; border-radius: 6px; font-weight: bold; font-size: 16px; display: inline-block;">Annuler la suppression</a>
				</div>
				<p style="color: #6b7280; font-size: 14px; margin-top: 30px;">Si le bouton ne fonctionne pas, copiez ce lien : <br>
				<a href="${recoveryLink}" style="color: #3b82f6;">${recoveryLink}</a>
				</p>
			</div>
		`,
		attachments: [
			{
				filename: 'arthub.png',
				path: './assets/arthub.png',
				cid: 'logo'
			}
		]
	};

	try {
		await transporter.sendMail(mailOptions);
	} catch (error) {
		console.error("Failed to send account deletion email:", error);
	}
}
