package com.nano.ctest;


import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
public class DetailActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_detail);

		Bundle bundle = getIntent().getExtras();
		
		TextView detailView = (TextView)findViewById(R.id.detailView);
		detailView.setText(bundle.getString("res"));
		
		TextView detailView_detail = (TextView)findViewById(R.id.detailView_detail);
		detailView_detail.setText(bundle.getString("trans") + "\n\n" + bundle.getString("examp"));
		// ·µ»ØÊÂ¼þ
		findViewById(R.id.btn_exit).setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				finish();
			}
		});
	}
}
