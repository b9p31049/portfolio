# Generated by Django 3.1.5 on 2021-02-07 15:26

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('todo', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='todomodel',
            name='duedate',
            field=models.DateField(default=django.utils.timezone.now),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='todomodel',
            name='priority',
            field=models.CharField(choices=[('dangar', 'high'), ('warning', 'normal'), ('prymary', 'low')], default='danger', max_length=50),
            preserve_default=False,
        ),
    ]
