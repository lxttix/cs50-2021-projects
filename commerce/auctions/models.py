from django.contrib.auth.models import AbstractUser, User
from django.db import models
from djmoney.models.fields import MoneyField
from django.core.validators import validate_comma_separated_integer_list

"""
need to add models to rep auction listings, bids, comments,
and auction categories

every time you change something, run:
python manage.py makemigrations 
python manage.py migrate
"""
class User(AbstractUser):
    pass


#hold auction listings
class Listing(models.Model):
    LISTING_CATEGORIES = (
        ("FA", "Clothes, Shoes, Jewellery & Accessories"),
        ("TO", "Toys, Children & Baby"),
        ("EL", "Electronics & Computers"),
        ("HO", "Home, Garden, Pets & DIY"),
        ("BO","Books"),
        ("FI", "Films, TV, Music & Games"),
        ("SP", "Sports & Outdoors"),
        ("FO", "Food & Grocery",),
        ("HE", "Health & Beauty"),
        ("CA", "Car & Motorbike"),
        ("BU", "Business, Industry & Science")
    )

    def __str__(self):
        return self.title
    
    def get_seller_username(self):
        return self.seller.username

    def get_category_display_name(self):
        return dict(self.LISTING_CATEGORIES).get(self.category, "Unknown Category")

    seller = models.ForeignKey(User, null=True, on_delete=models.CASCADE) #don't know how to access this
    title = models.CharField(max_length=20)
    description = models.TextField(null=True, blank=False)
    start_bid = MoneyField(currency_choices=[("GBP", ("British Pounds"))], max_digits=8)
    category = models.CharField(max_length=2, choices=LISTING_CATEGORIES)
    image_url = models.URLField(null=True, blank=True)

    start_bid_float = models.FloatField(null=True, blank=True)
    highest_bidding_price = models.FloatField(null=True, blank=True)
    status = models.BooleanField(null=True, blank=True)

#associates listings with specific users for watchlist
class Bidder(models.Model):
    user_id = models.OneToOneField(User, on_delete=models.CASCADE)
    watchList = models.ManyToManyField(Listing, related_name='watched_by', blank=True)

    def __str__(self):
        return f"{self.user_id.username}'s Watchlist"

#associates bids with listings and specific users
class Bid(models.Model):
    listing = models.ForeignKey(Listing, on_delete=models.CASCADE)
    highest_bidder = models.ForeignKey(User, on_delete=models.CASCADE)
    highest_price = models.FloatField(null=True, blank=True)
    bidding_price = models.FloatField(null=True, blank=True) #used to collect user input from the form
    total_bids = models.IntegerField(default=0)

    class Meta:
        unique_together = ('listing', 'highest_bidder')

    def __str__(self):
        return f"{self.highest_bidder} on {self.listing}"
    

#hold comments
#associates comments with a listing and user
class Comment(models.Model):
    listing = models.ForeignKey(Listing, null=True, on_delete=models.CASCADE)
    posted_by = models.ForeignKey(User, null=True, on_delete=models.CASCADE)
    content = models.TextField(null=True)
