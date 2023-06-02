package com.example.lightbartest;

import android.content.Intent;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager2.widget.ViewPager2;

import com.example.lightbartest.ui.main.SectionsPagerAdapter;
import com.example.lightbartest.util.Constant;
import com.google.android.material.tabs.TabLayout;
import com.google.android.material.tabs.TabLayoutMediator;

public class MainActivity extends AppCompatActivity {

    private ViewPager2 viewPager;
    private final String[] tab_title = {"UserControl", "UserFeature", "PowerSuspend", "PowerOff"};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        tabLayoutInit();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        final Intent intent = new Intent();
        final Bundle b = new Bundle();
        b.putBoolean(Constant.IS_LED_SERVICE_START, false);
        intent.setPackage(this.getPackageName());
        intent.setClass(this, LedModeService.class);
        stopService(intent);
        super.onDestroy();
    }

    private void tabLayoutInit() {
        TabLayout tabLayout = findViewById(R.id.tabLayout);
        viewPager = findViewById(R.id.viewPager);

        viewPager.setAdapter(new SectionsPagerAdapter(getSupportFragmentManager(), getLifecycle()));

        viewPager.setUserInputEnabled(false);
        new TabLayoutMediator(tabLayout, viewPager, true, new TabLayoutMediator.TabConfigurationStrategy() {
            @Override
            public void onConfigureTab(@NonNull TabLayout.Tab tab, int position) {
                viewPager.setCurrentItem(tab.getPosition());
            }
        }).attach();
        for (int i = 0; i < tabLayout.getTabCount(); i++) {
            tabLayout.getTabAt(i).setText(tab_title[i]);
        }
        tabLayout.setTabMode(TabLayout.MODE_FIXED);
        tabLayout.setTabGravity(TabLayout.GRAVITY_FILL);
        tabLayout.getTabAt(0).setIcon(R.drawable.settings);
        tabLayout.getTabAt(1).setIcon(R.drawable.wave);
        tabLayout.getTabAt(2).setIcon(R.drawable.sleep);
        tabLayout.getTabAt(3).setIcon(R.drawable.onoff);
    }
}