import random
import string
from PIL import Image, ImageDraw, ImageFont, ImageFilter

def generate_captcha_text(length=6):
    return ''.join(random.choices(string.ascii_uppercase + string.digits, k=length))

def generate_captcha_image(captcha_text):
    width, height = 150, 50
    background_color = (255, 255, 255)
    font_color = (0, 0, 0)
    font_size = 40

    image = Image.new('RGB', (width, height), background_color)
    draw = ImageDraw.Draw(image)

    try:
        font = ImageFont.truetype("arial.ttf", font_size)
    except:
        font = ImageFont.load_default()

    # Use textbbox to calculate the text size and position
    bbox = draw.textbbox((0, 0), captcha_text, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    text_position = ((width - text_width) // 2, (height - text_height) // 2)

    draw.text(text_position, captcha_text, font=font, fill=font_color)
    image = image.filter(ImageFilter.GaussianBlur(0.5))

    return image

def save_captcha_image(image, filename='captcha.png'):
    image.save(filename)
    print(f"Captcha image saved as {filename}")

def verify_captcha():
    captcha_text = generate_captcha_text()
    print("Generated CAPTCHA text:", captcha_text)

    captcha_image = generate_captcha_image(captcha_text)
    save_captcha_image(captcha_image)

    user_input = input("Enter the CAPTCHA text shown in the image: ")

    if user_input == captcha_text:
        print("CAPTCHA verification successful!")
    else:
        print("CAPTCHA verification failed.")

if __name__ == "__main__":
    verify_captcha()
