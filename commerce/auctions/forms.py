from django import forms
from .models import Listing, Bid, Comment

class NewListing(forms.ModelForm):
    class Meta:
        model = Listing
        fields = ["title", "description", "category", "image_url", "start_bid"]


class NewBid(forms.ModelForm):
    class Meta:
        model = Bid
        fields = ["bidding_price"]

class NewComment(forms.ModelForm):
    class Meta:
        model = Comment
        fields = ["content"]
    
